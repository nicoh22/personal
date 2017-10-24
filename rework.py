import random
#import sys
import time
import scapy.all as sp
import numpy as np
import requests as req
#from scipy import stats
#from os import getuid, stat

class TraceRoute():#MethodObject jajaja
    def _init_(self, dst):
        #config
        self.tamRafaga = 3
        self.cantReintentos = 3
        self.timeout = 1000#ms
        self.maxTtl = 20
        
        self.destino = sp.Net(dst)
        self.echoRequests = sp.IP(dst=self.destino, ttl=(1,self.maxTtl)) / sp.ICMP()



    def trace():
        for request in self.echoRequests
            request[sp.ICMP].id = random.randint(0, 65535)
            respuestas = []
            for medicion in range(tamRafaga):
                for reintento in range(self.cantReintentos):
                    tiempoInicio = time.perf_counter()
                    respuesta = sp.sr(request)
                    tiempoFin = time.perf_counter()
                    rtt = tiempoFin - tiempoInicio
                    if respuesta is not None:
                        ip_respuesta = respuesta.src
                        respuestas.append((ip_respuesta, rtt))
                        llegamos_a_destino = destino == ip_respuesta
                        break

            #hop, rttToHop = self.analizarRespuestas(respuestas)
            echoResponse = self.analizarRespuestas(respuestas)
            #TODO procesar datos obtenidos
            if self.destino == respuesta:
                break


    def analizarRespuestas(self, respuestas):
        #something




#def main(destino, maximo_ttl, timeout_por_ttl, mediciones_por_ttl, reintentos_por_ttl):


if __name__ == "__main__":

    route = TraceRoute("www.google.com")
    output = JsonBuilder(route)
    print(output)
