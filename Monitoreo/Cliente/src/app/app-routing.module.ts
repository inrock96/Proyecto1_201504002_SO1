import { NgModule } from '@angular/core';
import { Routes, RouterModule } from '@angular/router';
import { CPUComponent } from './components/cpu/cpu.component';
import { HomeComponent } from './components/home/home.component';
import { MemoriaComponent } from './components/memoria/memoria.component';


const routes: Routes = [
  {
    path:'',redirectTo:'/home',pathMatch:'full',
  },
  {
    path:'home',
    component:HomeComponent
  },
  {
    path:"memoria",
    component:MemoriaComponent
  },
  {
    path:"cpu",
    component:CPUComponent
  }
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
