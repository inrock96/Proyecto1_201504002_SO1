import { Injectable } from '@angular/core';
import { Socket } from 'net';

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
    this.webSocket = new WebSocket(`${this.WS_URI}/ws`);
    this.webSocket.onopen = (event)=>{
      console.log('Open: ',event)
    }
    this.webSocket.onmessage= msg=>{
      if(msg.data!="RAM"){
        const chatMessageDto = JSON.parse(msg.data);
        this.mensajes.push(chatMessageDto);
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
