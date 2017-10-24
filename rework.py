#import random
#import sys
import time
import scapy.all as sp
import numpy as np
import requests as req
#from scipy import stats
#from os import getuid, stat

class TraceRoute():#MethodObject jajaja
    def _init_(self, dst):
        self.destino = sp.Net(dst)
        self.echoRequests = sp.IP(dst=self.destino, ttl=(1,maxTtl)) / sp.ICMP()#ok, un paquete por ttl

    def xxx():
        for paquete in self.echoRequests
            paquete[sp.ICMP].id = random.randint(0, 65535)
            respuestas = []
            for medicion in range(medicionesPorTtl):#cambiar nombres?
                for reintento in range(self.tamRafaga):
                    tiempoInicio = time.perf_counter()
                    respuesta = sp.sr(paquete)
                    tiempoFin = time.perf_counter()
                    rtt = tiempoFin - tiempoInicio
                    if respuesta is not None:
                        respuestas.append(respuesta)
                        #esto creo que no va, 
                        #Nosotros queremos reintentar varias veces para cada
                        #ttl, con el fin de encontrar varias ruta o tomar rtt promediado.
                        break


#def main(destino, maximo_ttl, timeout_por_ttl, mediciones_por_ttl, reintentos_por_ttl):


if __name__ == "__main__":

    route = TraceRoute("www.google.com")
    output = JsonBuilder(route)
    print(output)
