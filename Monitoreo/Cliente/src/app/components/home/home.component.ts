import { Component, OnInit } from '@angular/core';
import { ListaProceso } from 'src/app/models/ListaProceso';
import { Proceso } from 'src/app/models/Proceso';
import { WebSocketService } from 'src/app/services/web-socket.service';

@Component({
  selector: 'app-home',
  templateUrl: './home.component.html',
  styleUrls: ['./home.component.css']
})
export class HomeComponent implements OnInit {
  lista:ListaProceso
  procesos:Proceso[]
  constructor(private wsService:WebSocketService) { 
    this.lista={
      procesos:[],
      detenido:0,
      ejecucion:0,
      otros:0,
      total:0,
      suspendido:0,
      zombie:0
    }
  }

  ngOnInit() {
    this.wsService.openWebSocket();
    setInterval(()=>{
      try {
        this.wsService.enviarMensaje('PRINCIPAL');
        const lista = this.wsService.mensajes.pop()
        this.lista = <ListaProceso>lista;
      } catch (error) {
          
      }  
      
    },2000)
  }
  
  ngOnDestroy(){
    this.wsService.closeWebSocket();
  }
  kill(pid){
    this.wsService.enviarMensaje(pid);
  }

}
