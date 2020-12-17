package main

import (
	"C"
	"fmt"
	"log"
	"net/http"

	"github.com/gorilla/websocket"
)
import (
	"encoding/json"
	"io/ioutil"
	"os/exec"
	"strconv"
	"strings"
	"syscall"
	"time"
)

//Proceso es la estructura para exportar un proceso
type Proceso struct {
	PID     string `json:"pid"`
	Nombre  string `json:"nombre"`
	Usuario string `json:"usuario"`
	Estado  string `json:"estado"`
}

//ListaProceso una lista de procesos
type ListaProceso struct {
	Procesos         []Proceso `json:"procesos"`
	TotalEjecucion   string    `json:"ejecucion"`
	TotalSuspendidos string    `json:"suspendido"`
	TotalDetenidos   string    `json:"detenido"`
	TotalZombie      string    `json:"zombie"`
	TotalOtros       string    `json:"otros"`
	TotalProcesos    string    `json:"total"`
}

//Memoria es la estructura para exportar datos de la memoria
type Memoria struct {
	MemTotal   string `json:"MemTotal"`
	MemFree    string `json:"MemFree"`
	MemPercent string `json:"MemPercent"`
}

//CPUInfo es la estructura para exportar datos del cpu
type CPUInfo struct {
	CPUPercent string `json:"CPUPercent"`
}

var upgrader = websocket.Upgrader{
	ReadBufferSize:  1024,
	WriteBufferSize: 1024,
	CheckOrigin:     func(r *http.Request) bool { return true },
}

var clients = make(map[*websocket.Conn]string)

func wsEndpoint(w http.ResponseWriter, r *http.Request) {
	upgrader.CheckOrigin = func(r *http.Request) bool { return true }

	ws, err := upgrader.Upgrade(w, r, nil)
	if err != nil {
		log.Println(err)
	}
	log.Println("Cliente conectado con éxito")
	reader(ws)
}

func reader(conn *websocket.Conn) {

	for {
		messageType, p, err := conn.ReadMessage()
		if err != nil {
			log.Println(err)
			return
		}
		log.Println(string(p))
		clients[conn] = string(p)
		if err := conn.WriteMessage(messageType, p); err != nil {
			log.Println(err)
			return
		}

	}
}

func envioInfo() {
	for {
		for client := range clients {
			var value string = clients[client]
			log.Println(value)
			salidaLista := ListaProceso{}
			var memo *Memoria
			if value == "PRINCIPAL" {
				//PAGINA PRINCIPAL
				data, err := ioutil.ReadFile("/proc/cpu_201504002")

				if err != nil {
					fmt.Println("Error de lectura de archivo cpu_201504002")
					return
				}

				strData := string(data)
				if erroJS := json.Unmarshal([]byte(strData), &salidaLista); erroJS != nil {
					log.Printf("error %v", erroJS)
					client.Close()
					delete(clients, client)
				}

				//regresar respuesta salidalista
				if errW := client.WriteJSON(salidaLista); errW != nil {
					log.Printf("error %v", errW)
					client.Close()
					delete(clients, client)
				}
			} else if value == "RAM" {
				data, err := ioutil.ReadFile("/proc/memo_201504002")
				if err != nil {
					fmt.Println("Error de lectura memo_201504002")
					return
				}
				strData := string(data)
				json.Unmarshal([]byte(strData), &memo)
				errW := client.WriteJSON(memo)
				if errW != nil {
					log.Printf("error %v", errW)
					client.Close()
					delete(clients, client)
				}
			} else if value == "CPU" {
				cmd := exec.Command("sh", "-c", "ps -eo pcpu | sort -k 1 -r | head -50")
				out, err := cmd.CombinedOutput()
				if err != nil {
					log.Fatal(err)
				}

				//go fmt.Println("CPU obtenido correctamente")

				output := string(out[:])
				//fmt.Fprintf(w, output)
				s := strings.Split(output, "\n")
				cpuUsado := 0.0
				for i := 1; i < 51; i++ {

					valor, err := strconv.ParseFloat(strings.Trim(s[i], " "), 64)
					if err != nil {
						//go fmt.Println("valorError ->" + s[i] + "<-" + strconv.Itoa(i))
						//go fmt.Println(err)
					}

					cpuUsado += valor
					//go fmt.Println("valor ->" + s[i] + "<-" + strconv.Itoa(i))
				}
				strData := fmt.Sprint(cpuUsado)
				strData = "{\"MemTotal\":\"0\",\"MemFree\":\"0\",\"MemPercent\":\"" + strData + "\"}"
				json.Unmarshal([]byte(strData), &memo)
				errW := client.WriteJSON(memo)
				if errW != nil {
					log.Printf("error %v", errW)
					client.Close()
					delete(clients, client)
				}
			} else {
				killHandler(value)
			}
		}
		log.Println(len(clients))
		log.Printf("------------------")
		time.Sleep(2000 * time.Millisecond)
	}
}
func killHandler(pid string) {
	arg0 := pid
	val0, _ := strconv.ParseInt(arg0, 10, 32)
	pidfind := int(val0)
	err := syscall.Kill(pidfind, 9)
	if err != nil {
		log.Printf("error %v", err)
	}
}

func main() {
	fmt.Println("Go Websockets")
	fs := http.FileServer(http.Dir("./static"))
	http.Handle("/static/", http.StripPrefix("/static/", fs))
	http.Handle("/", fs)
	http.HandleFunc("/ws", wsEndpoint)
	go envioInfo()
	log.Println("listening on port 3000")
	err := http.ListenAndServe(":3000", nil)
	if err != nil {
		log.Fatal(err)
	}
}
