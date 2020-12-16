import { Component, OnInit , ViewChild} from '@angular/core';
import { ChartDataSets, ChartOptions} from 'chart.js';
import { Color, Label,ThemeService } from 'ng2-charts';
import { BaseChartDirective } from "ng2-charts";
import {Chart} from 'chart.js';
@Component({
  selector: 'app-cpu',
  templateUrl: './cpu.component.html',
  styleUrls: ['./cpu.component.css'],
  providers:[ThemeService]
})
export class CPUComponent implements OnInit {

  @ViewChild( BaseChartDirective, {static: false}) chart: BaseChartDirective;
  // lineChart
  public label = 10;
  public a = 0;
  
  public lineChartData: Array<any> = [0, 0, 0, 0, 0, 0, 0, 0,0,0,0];
  
  public lineChartLabels: Array<any> = ["1", "2", "3", "4", "4", "5", "6", "7", "8", "9"];
  public lineChartOptions: any = {
    responsive: true,
    scales: {
      yAxes: [
        {
          ticks: {
            //  steps : 25,
            //  stepValue : 15,
            //  max : 40,
            min: 0
          }
        }
      ]
    }
  };
  
  public labelMFL: Array<any> = [{ data: this.lineChartData, label: "Memoria Utilizada" }];
  
  public lineChartColors: Array<any> = [
    {
      // grey
      backgroundColor: "rgba(148,159,177,0.2)",
      borderColor: "rgba(148,159,177,1)",
      pointBackgroundColor: "rgba(148,159,177,1)",
      pointBorderColor: "#fff",
      pointHoverBackgroundColor: "#fff",
      pointHoverBorderColor: "rgba(148,159,177,0.8)"
    }
  ];
  // public lineChartLegend: boolean = true;
  public lineChartType = "line";
  
  // events
  public chartClicked(e: any): void {
    console.log(e);
  }
  
  public chartHovered(e: any): void {
    console.log(e);
  }
  
  constructor() {}
  
  ngOnInit() {
    setInterval(() => {
      const _lineChartData = this.lineChartData;
      const _lineChartLabels = this.lineChartLabels;
      _lineChartData.push(Math.floor(Math.random() * 100 + 1));
      _lineChartLabels.push(this.label);
      this.label++;
      this.lineChartData.splice(0, 1);
      this.lineChartLabels.splice(0, 1);
      this.lineChartData = _lineChartData;
      this.lineChartLabels = _lineChartLabels;
      this.chart.chart.update();
    }, 10000);
  }

}
