import { Injectable } from '@angular/core';

@Injectable({
  providedIn: 'root'
})
export class WebSocketService {
  WS_URI = 'ws://localhost:3000';
  webSocket:WebSocket;
  mensajes:any;
  memoria:any
  cpu:any
  procesos:any
  constructor() { }
  public openWebSocket(){
    this.mensajes = []
    this.webSocket = new WebSocket(`${this.WS_URI}/ws`);
    this.webSocket.onopen = (event)=>{
      console.log('Open: ',event)
    }
    this.webSocket.onmessage= msg=>{
      try {
        const chatMessageDto = JSON.parse(msg.data);
        this.mensajes.push(chatMessageDto);
      } catch (error) {
        
      } 
      
    }
    this.webSocket.onclose = (event)=>{
      console.log('Close: ',event)
    }
  }
  public enviarMensaje(mensaje:string){
    this.webSocket.send(mensaje);

  }
  public closeWebSocket(){
    this.webSocket.close();
  }
}
