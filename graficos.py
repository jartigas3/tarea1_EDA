import matplotlib.pyplot as plt
import numpy as np


ND = np.array([10000, 50000, 100000, 200000, 400000])

# Tiempos en milisegundos 
AS_time = np.array([126991, 609211, 1180780, 2192444, 3724913])  
BB_time = np.array([297, 359, 391, 443, 607])  
Sort_time = np.array([3, 19, 48, 95, 190])  
BB_with_sort_time = BB_time + Sort_time  

plt.figure(figsize=(10, 6))
plt.plot(ND, AS_time, marker='o', label="AS - Búsqueda Secuencial")
plt.plot(ND, BB_time, marker='o', label="BB - Búsqueda Binaria (sin sort)")
plt.plot(ND, BB_with_sort_time, marker='o', label="BB + Sort - Búsqueda Binaria (con sort)")

plt.title("Comparación de Tiempos de Búsqueda")
plt.xlabel("Tamaño del Diccionario (ND)")
plt.ylabel("Tiempo de Ejecución (ms)")
plt.legend()
plt.grid(True)

plt.show()
