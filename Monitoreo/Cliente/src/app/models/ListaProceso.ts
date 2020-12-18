import {Proceso} from './Proceso'
export interface ListaProceso{
    procesos:Proceso[],
    ejecucion :  number,
	suspendido :number, 
	detenido :  number, 
	zombie  :    number, 
	otros :      number, 
	total   : number 
}