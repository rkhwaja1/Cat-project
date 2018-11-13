This code is for a biological model of two neuron central pattern generator (CPG) in a cat. Central pattern generators are neural networks in the spinal cord of vertebrates that control rhythmic muscular activity. This code models the muscular voltages in a single leg of a cat

In my code, All computations are written using C while the visualizations of the computations can be run using MATLAB. I have formatted the MATLAB code so it should be able to run in Octave if that's your scientific computing language of choice.

Please install The GSL scientific library component for GNU to use this code. 

Summary of files:
The HN4_Main file contains all of the value for the parameters used in this model. 
The differential equations which model the CPG are present on the HN4_dy.c file
The hn4_h file declares the variables and in the model.
hn4_integrate and hn4_integrateNW integrates the differential equations for the time listed in the hn4_main file.
burstdata.c analyzes the muscular activity that the CPG generates.

plotVT.m (MATLAB code) visualizes the muscular voltages that each of the two neurons.