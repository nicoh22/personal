import random
#import sys
import time
import scapy.all as sp
import numpy as np
import requests as req
#from scipy import stats
from os import getuid, stat
from collections import Counter
import json

class TraceRoute():#MethodObject jajaja
    def __init__(self, dst):
        #config
        self.tamRafaga = 3
        self.cantReintentos = 3
        self.timeout = 0.5#segs?
        self.maxTtl = 20

        self.destino = sp.Net(dst)
        self.echoRequests = sp.IP(dst=self.destino, ttl=(1,self.maxTtl)) / sp.ICMP()
        self.traced = []
        self.trace()

    def trace(self):
        hopCount = 1
        for request in self.echoRequests:
            request[sp.ICMP].id = random.randint(0, 65535)
            respuestas = []
            destinoAlcanzado = False
            for medicion in range(self.tamRafaga):
                for reintento in range(self.cantReintentos):
                    tiempoInicio = time.perf_counter()
                    respuesta = sp.sr1(request,timeout=self.timeout)
                    tiempoFin = time.perf_counter()
                    rtt = tiempoFin - tiempoInicio#TODO chequear que sean milisegundos
                    if respuesta is not None:
                        respuestas.append((respuesta.src, rtt))
                        destinoAlcanzado = self.destino == respuesta.src 
                        break

            hop, rttToHop = self.analizarRespuestas(respuestas)
            #TODO geolocalizar aqui
            self.traced.append({"rtt":rttToHop, "ip_address":hop, "salto_internacional":False, "hop_num":hopCount})
                
            hopCount = hopCount + 1 
            #if hop is not None:
            #    mediciones.append((request.ttl, hop, rttToHop))

            if destinoAlcanzado:
                break

        #Todo lo siguiente puede ir en un metodo aparte no?
        #self.detectarOutliers(mediciones)


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

    def detectarOutliers(self, mediciones):
        rttDifs = []
        rttAnterior = 0

        for medicion in mediciones:
            rttDifs.append(float(medicion[2]) - rttAnterior)

        outliersStandard = self.cimbalaStandard(rttDifs)
        #outliersRemoviendo = self.cimbalaRemoviendo(rttDifs)

        return outliersStandard#, outliers_removiendo
        
    def cimbalaStandard(self, rttDifs):
        outliers = []
        if len(rttDifs) > 0:
            media = np.mean(rttDifs)
            desvio_standard = np.std(rttDifs)
            tg = thompson_gamma(rttDifs)
            #falta completar los calculos

        for rttDif in rttDifs:
            delta = np.absolute(rttDif - media)
            if (delta > tg * desvio_standard):
                outliers.append(rttDif)
                #print("outlier: " + str(int(rttDif * 1000)))
        return outliers
		


#def main(destino, maximo_ttl, timeout_por_ttl, mediciones_por_ttl, reintentos_por_ttl):


if __name__ == "__main__":

    if getuid() != 0:
        print('Ejecutar como admin')
        exit(1)
    route = TraceRoute("www.google.com")
    print(json.dumps(route.traced, indent=4))
