import {Proceso} from './Proceso'
export interface ListaProceso{
    Procesos:Proceso[],
    ejecucion :  number,
	suspendido :number, 
	detenido :  number, 
	zombie  :    number, 
	otros :      number, 
	total   : number 
}