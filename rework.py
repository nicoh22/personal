import random
#import sys
import time
import scapy.all as sp
import numpy as np
import requests as req
#from scipy import stats
#from os import getuid, stat
from collections import Counter

class TraceRoute():#MethodObject jajaja
    def _init_(self, dst):
        #config
        self.tamRafaga = 3
        self.cantReintentos = 3
        self.timeout = 1000#ms
        self.maxTtl = 20
        
        self.destino = sp.Net(dst)
        self.echoRequests = sp.IP(dst=self.destino, ttl=(1,self.maxTtl)) / sp.ICMP()
        self.route = []



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

            hop, rttToHop = self.analizarRespuestas(respuestas)
            if hop is not None:
                mediciones.append((request.ttl, hop, rttToHop))

            self.route.append((hop,rttToHop))#ponele que necesito esto
            if self.destino == respuesta:
                break
        detectarOutliers(mediciones)


    def analizarRespuestas(self, respuestas):
        #TODO hay una forma mas copada de decir respuesta[0]
        #ips = [res[0] for res in respuestas]
        #ipCount = Counter(ips)

        ipDict = {}
        for respuesta in respuestas:
            if respuesta[0] in ipDict:
                rttAcumulado, cantidadAcumulada = ipDict[respuesta[0]]
                ipDict[respuesta[0]] = (rttAcumulado + respuesta[1], cantidadAcumulada + 1)
            else:
                ipDict[respuesta[0]] = (respuesta[1], 1)
        
        cantidadMaxima = 0
        ipElegida = None
        rttPromedio = 0
        for ip in ipDict.keys():
            rttAcum, cant = ipDict[ip]
            if cant > cantidadMaxima:
                cantidadMaxima = cant
                ipElegida = ip
                rttPromedio = rttAcum / cant

        return ipElegida, rttPromedio





#def main(destino, maximo_ttl, timeout_por_ttl, mediciones_por_ttl, reintentos_por_ttl):


if __name__ == "__main__":

    route = TraceRoute("www.google.com")
    output = JsonBuilder(route)
    print(output)
