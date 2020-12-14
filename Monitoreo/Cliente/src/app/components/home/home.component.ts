import { Component, OnInit } from '@angular/core';
import { WebSocketService } from 'src/app/services/web-socket.service';

@Component({
  selector: 'app-home',
  templateUrl: './home.component.html',
  styleUrls: ['./home.component.css']
})
export class HomeComponent implements OnInit {

  constructor(private wsService:WebSocketService) { }

  ngOnInit() {
    this.wsService.openWebSocket();
  }
  
  ngOnDestroy(){
    this.wsService.closeWebSocket();
  }
  enviar(){
    this.wsService.enviarMensaje('home');
  }

}
