'use strict'

/* GESTIÓN SIDEBARS */

$(function() {
    // Side Bar Toggle
    $('.hide-sidebar').click(function() {
	  $('#sidebar').hide('fast', function() {
	  	$('#content').removeClass('span9');
	  	$('#content').addClass('span12');
	  	$('.hide-sidebar').hide();
	  	$('.show-sidebar').show();
	  });
	});
	$('.show-sidebar').click(function() {
		$('#content').removeClass('span12');
	   	$('#content').addClass('span9');
	   	$('.show-sidebar').hide();
	   	$('.hide-sidebar').show();
	  	$('#sidebar').show('fast');
	});
});

/* GESTIÓN CONEXIONES */

//WebSocket Conexión
var connection = new WebSocket('ws://' + location.hostname + '/ws', ['arduino']);
//Abrir el WebSocket
connection.onopen = function() {console.log('WS/ Connectado');};
//Error
connection.onerror = function(error) {console.log('WS/ Error ', error);};
//Cuando llega Mensaje llamamos la Función ProcessData
connection.onmessage = function(e) {
    console.log('Server: ', e.data);
    processData(e.data);
};
//Cerrar el Websocket
connection.onclose = function() {console.log('WS/ Cerrado');};
//Camturar el Pathname del URL
let pathname = window.location.pathname;

/* ACTUALIZACIÓN CONSTANTE DE DATOS RECIBIDOS */

function processData(data) 
{
    //Convertir la Data en Json
    let json = JSON.parse(data);
    //Si estamos en el panel de control actualizamos los valores
    if (pathname == "/") {
        if (json.WFEstatus != null) {
            let WFEstatus = document.getElementById('WFEstatus');
            let WFDBM = document.getElementById('WFDBM');
            let WFPRC = document.getElementById('WFPRC');
            let WiFiChart = document.getElementById('WiFiChart');
            let PMEMChart = document.getElementById('PMEMChart');
            let ramChart = document.getElementById('ramChart');
            let cpuChart = document.getElementById('cpuChart');
            let luzDormChart = document.getElementById('luzDormchart');
            let luzHabChart = document.getElementById('luzHabchart');
            let luzActDorm = document.getElementById('valorActDorm');
            let luzActHab = document.getElementById('valorActHab');
            let diaNoche = document.getElementById('diaNoche');
            let consumoVerano = document.getElementById('consumoDiaVerano');
            let consumoInvierno = document.getElementById('consumoDiaInvierno');
            WFEstatus.innerHTML = json.WFEstatus;
            WFDBM.innerHTML = json.WFDBM + " dBm";
            WFPRC.innerHTML = json.WFPRC + " %";
            WiFiChart.innerHTML = json.WFPRC + " %";
            PMEMChart.innerHTML = json.PMEM + " %";
            ramChart.innerHTML = json.ram + " %";
            cpuChart.innerHTML = json.cpu + " °C";
            luzDormChart.innerHTML = json.luzDorm + " %";
            luzHabChart.innerHTML = json.luzHab + " %";
            luzActDorm.innerHTML = json.valorActDorm + " %";
            luzActHab.innerHTML = json.valorActHab + " %";
            consumoVerano.innerHTML = json.consumoVerano + " mWh";
            consumoInvierno.innerHTML = json.consumoInvierno + " mWh";
            $(function() {
                var chart = window.chart = $('#chartWiFi').data('easyPieChart');
                chart.update(json.WFPRC);
                var chart = window.chart = $('#chartPMEM').data('easyPieChart');
                chart.update(json.PMEM);
                var chart = window.chart = $('#chartram').data('easyPieChart');
                chart.update(json.ram);
                var chart = window.chart = $('#chartcpu').data('easyPieChart');
                chart.update(json.cpu);
                var chart = window.chart = $('#chartluzDorm').data('easyPieChart');
                chart.update(json.luzDorm);
                var chart = window.chart = $('#chartluzHab').data('easyPieChart');
                chart.update(json.luzHab);
            });

            /* GESTIÓN DE INDICADORES RELACIONADOS CON INFORMACIÓN RECIBIDA */

            // Datos sensores y actuadores
            let estadoLed1 = json.led1;
            let estadoLed2 = json.led2;
            let presDorm = json.presDorm;
            let presHab = json.presHab;
            let esNoche = json.esNoche;
            // LED dormitorio: Si está encendido se simula de igual forma
            let bulb = document.querySelector("#light");
            if(estadoLed1 == "1")
            {
                bulb.classList.add("on");
            } else{
                bulb.classList.remove("on");
            }
            // LED habitación: Si está encendido se simula de igual forma
            let bulb2 = document.querySelector("#light2");
            if(estadoLed2 == "1")
            {
                bulb2.classList.add("on");
            } else{
                bulb2.classList.remove("on");
            }
            // Presencia dormitorio: Si se detecta se enciende la alarma
            let pres1 = document.querySelector("#presDorm");
            if(presDorm == "1")
            {
                pres1.classList.add("activ");
            } else{
                pres1.classList.remove("activ");
            }
            // Presencia habitación: Si se detecta se enciende la alarma
            let pres2 = document.querySelector("#presHab");
            if(presHab == "1")
            {
                pres2.classList.add("activ");
            } else{
                pres2.classList.remove("activ");
            }
            // Botones de día: visibiliza los botones accesibles de noche si es de noche
            let botones = document.querySelector("#botonesDia");
            if(esNoche == '0')
            {
                botones.classList.add("desactivado");
                diaNoche.innerHTML = "DÍA";
            }
            else
            {
                botones.classList.remove("desactivado");
                diaNoche.innerHTML = "NOCHE";
            }
        }
    }
}

/* ****************** FUNCIONES ADICIONALES ****************** */

// Restablece la conexión WiFi
function restablecer() {

    Swal.fire({
        title: 'Restablecer!',
        text: ' ¿Está seguro de restablecer el equipo?',
        icon: 'warning',
        showCancelButton: true,
        confirmButtonColor: '#3085d6',
        cancelButtonColor: '#d33',
        confirmButtonText: 'Si, restablecer',
        cancelButtonText: 'Cancelar',
        reverseButtons: true
    }).then((result) => {
        if (result.isConfirmed) {
            window.location = "reconfig";
        } else if (
            result.dismiss === Swal.DismissReason.cancel
        ) {
            history.back();
        }
    })

}

/* GUARDADO DE VALORES DE SLIDERS 
   Actualiza el valor en el identificador numérico
   correspondiente.*/

// Valor del dormitorio
const sliderDorm = document.getElementById("rangoDorm");
const valueDorm = document.getElementById("valueDorm");
valueDorm.innerHTML = sliderDorm.value;
sliderDorm.oninput = function(){
    valueDorm.innerHTML = this.value;
}
// Valor de la habitación
const sliderHab = document.getElementById("rangoHab");
const valueHab = document.getElementById("valueHab");
valueHab.innerHTML = sliderHab.value;
sliderHab.oninput = function(){
    valueHab.innerHTML = this.value;
}

/* GESTIÓN DE TABS DE MODOS 
   Hace visible el tab pulsado (o activo por defecto)
   e invisible el resto.*/

const li = document.querySelectorAll('.li');
const bloque = document.querySelectorAll('.bloque');
li.forEach((cadaLi , i)=>{
    li[i].addEventListener('click', ()=>{
        li.forEach((cadaLi, i)=>{
            li[i].classList.remove('activo')
            bloque[i].classList.remove('activo')
        })
        li[i].classList.add('activo')
        bloque[i].classList.add('activo')
    })
})

/* FUNCIONES DE ENCENDIDO Y APAGADO MANUAL DE LEDS 
   (envía la información al microcontrolador para que lo haga) */

// Enciende LED dormitorio
function LedDormOn()
{  
  let data = {
    command : "DormOn",
  }
  let json = JSON.stringify(data);
  connection.send(json);
}
// Apaga LED dormitorio
function LedDormOff()
{  
  let data = {
    command : "DormOff",
  }
  let json = JSON.stringify(data);
  connection.send(json);
}
// Enciende LED habitación
function LedHabOn()
{  
  let data = {
    command : "HabOn",
  }
  let json = JSON.stringify(data);
  connection.send(json);
}
// Apaga LED habitación
function LedHabOff()
{ 
  let data = {
    command : "HabOff",
  }
  let json = JSON.stringify(data);
  connection.send(json);
}

/* ENVÍA LA CONFIGURACIÓN ESTABLECIDA 
   (envía la información al microcontrolador para que lo haga)  */

function configData()
{
    let sliderDorm = document.getElementById("rangoDorm");
    let sliderHab = document.getElementById("rangoHab");
    let data = {
        command : "configData",
        valueDorm : sliderDorm.value,
        valueHab : sliderHab.value,
    }
    let json = JSON.stringify(data);
    connection.send(json);
}

/* FUNCIONES DE CAMBIO DE MODO 
   (envía la información al microcontrolador para que lo haga)  */

// Cambia al modo manual
function ModoManual()
{
    let container = document.querySelector("#container");
    container.classList.remove("corto");
    container.classList.add("largo");
    let data = {
        command : "ModoManual",
    }
    let json = JSON.stringify(data);
    connection.send(json);
}
// Cambia al modo inteligente
function ModoInteligente()
{
    let container = document.querySelector("#container");
    container.classList.remove("largo");
    container.classList.add("corto");
    let data = {
        command : "ModoInteligente",
    }
    let json = JSON.stringify(data);
    connection.send(json);
}

/* FUNCIONES DE CAMBIO DE DÍA/NOCHE 
   (envía la información al microcontrolador para que lo haga)  */

// Cambia a día
function cambioDia()
{
    let data = {
        command : "cambioDia",
      }
      let json = JSON.stringify(data);
    
      connection.send(json);
}
// Cambia a noche
function cambioNoche()
{
    let data = {
        command : "cambioNoche",
      }
      let json = JSON.stringify(data);
    
      connection.send(json);
}

/* FUNCIONES DE CAMBIO DE COMPORTAMIENTO MODO MANUAL 
   (envía la información al microcontrolador para que lo haga)  */

// Cambia a comportamiento respetuoso
function cambioRespetuoso()
{
    let respetuoso = document.querySelector("#botonRespetuoso");
    let despistado = document.querySelector("#botonDespistado");
    let pasota = document.querySelector("#botonPasota");
    despistado.classList.remove("btn-primary");
    pasota.classList.remove("btn-primary");
    despistado.classList.add("btn-info");
    pasota.classList.add("btn-info");
    respetuoso.classList.add("btn-primary");
    respetuoso.classList.remove("btn-info");
    let infoRespetuoso = document.querySelector("#infoRespetuoso");
    let infoDespistado = document.querySelector("#infoDespistado");
    let infoPasota = document.querySelector("#infoPasota");
    infoRespetuoso.classList.remove("desactivado");
    infoDespistado.classList.add("desactivado");
    infoPasota.classList.add("desactivado");

    let data = {
    command : "Respetuoso",
    }
    let json = JSON.stringify(data);
    connection.send(json);
}
// Cambia a comportamiento despistado
function cambioDespistado()
{
    let respetuoso = document.querySelector("#botonRespetuoso");
    let despistado = document.querySelector("#botonDespistado");
    let pasota = document.querySelector("#botonPasota");
    respetuoso.classList.remove("btn-primary");
    pasota.classList.remove("btn-primary");
    respetuoso.classList.add("btn-info");
    pasota.classList.add("btn-info");
    despistado.classList.add("btn-primary");
    despistado.classList.remove("btn-info");
    let infoRespetuoso = document.querySelector("#infoRespetuoso");
    let infoDespistado = document.querySelector("#infoDespistado");
    let infoPasota = document.querySelector("#infoPasota");
    infoRespetuoso.classList.add("desactivado");
    infoDespistado.classList.remove("desactivado");
    infoPasota.classList.add("desactivado");

    let data = {
    command : "Despistado",
    }
    let json = JSON.stringify(data);
    connection.send(json);
}
// Cambia a comportamiento pasota
function cambioPasota()
{
    let respetuoso = document.querySelector("#botonRespetuoso");
    let despistado = document.querySelector("#botonDespistado");
    let pasota = document.querySelector("#botonPasota");
    respetuoso.classList.remove("btn-primary");
    despistado.classList.remove("btn-primary");
    respetuoso.classList.add("btn-info");
    despistado.classList.add("btn-info");
    pasota.classList.add("btn-primary");
    pasota.classList.remove("btn-info");
    let infoRespetuoso = document.querySelector("#infoRespetuoso");
    let infoDespistado = document.querySelector("#infoDespistado");
    let infoPasota = document.querySelector("#infoPasota");
    infoRespetuoso.classList.add("desactivado");
    infoDespistado.classList.add("desactivado");
    infoPasota.classList.remove("desactivado");

    let data = {
    command : "Pasota",
    }
    let json = JSON.stringify(data);
    connection.send(json);
}

/* FUNCIONES DE GESTIÓN DE AYUDAS DE LA PÁGINA
   Si se pulsan sus respectivos bloques, la información
   se hace visible o invisible */

// Información sección variables
let contVariables = 0;
function legoVariables()
{
    let info = document.querySelector("#infoVariables");
    if(contVariables == 0)
    {
        info.classList.remove("desactivado");
        contVariables = 1;
    }
    else{
        info.classList.add("desactivado");
        contVariables = 0;
    }
}
// Información sección red WiFi
let contRedWifi = 0;
function legoRedWifi()
{
    let info = document.querySelector("#infoRedWifi");
    if(contRedWifi == 0)
    {
        info.classList.remove("desactivado");
        contRedWifi = 1;
    }
    else{
        info.classList.add("desactivado");
        contRedWifi = 0;
    }
}
// Información sección configuración habitaciones
let contConfigHab = 0;
function legoConfigHab()
{
    let info = document.querySelector("#infoConfigHab");
    if(contConfigHab == 0)
    {
        info.classList.remove("desactivado");
        contConfigHab = 1;
    }
    else{
        info.classList.add("desactivado");
        contConfigHab = 0;
    }
}
// Información sección actuadores
let contActuadores = 0;
function legoActuadores()
{
    let info = document.querySelector("#infoActuadores");
    if(contActuadores == 0)
    {
        info.classList.remove("desactivado");
        contActuadores = 1;
    }
    else{
        info.classList.add("desactivado");
        contActuadores = 0;
    }
}
// Información sección sensores
let contSensores = 0;
function legoSensores()
{
    let info = document.querySelector("#infoSensores");
    if(contSensores == 0)
    {
        info.classList.remove("desactivado");
        contSensores = 1;
    }
    else{
        info.classList.add("desactivado");
        contSensores = 0;
    }
}
// Información sección casa
let contCasa = 0;
function legoCasa()
{
    let info = document.querySelector("#infoCasa");
    if(contCasa == 0)
    {
        info.classList.remove("desactivado");
        contCasa = 1;
    }
    else{
        info.classList.add("desactivado");
        contCasa = 0;
    }
}
// Información sección final
let contFinal = 0;
function legoFinal()
{
    let info = document.querySelector("#infoFinal");
    if(contFinal == 0)
    {
        info.classList.remove("desactivado");
        contFinal = 1;
    }
    else{
        info.classList.add("desactivado");
        contFinal = 0;
    }
}