# Accurate False-positive Probability of Multiset-based Demirci-Selçuk Meet-in-the-middle Attacks

## Overview

This repository contains codes for accurately calculating the false-positive probability and conducting toy experiments for the paper titled ''Accurate False-positive Probability of Multiset-based Demirci-Selçuk Meet-in-the-middle Attacks.''

## Contents

### accurate_calculation_of_fpp.py
This script provides the function to calculate the accurate false-positive probability given parameters N, u, v (delta(1, N, u, v)). It is currently set up to calculate the values needed for Tables 3 and 4.

### Accurate_Calculation_Results.txt
This file contains the execution results of **accurate_calculation_of_fpp.py**.

### sampling_sequences_AES.cpp, sampling_sequences_ARIA
These scripts are used for sampling sequences. Running these scripts will generate the text files named **Sampling_Result_AES.txt** and **Sampling_Result_ARIA.txt**, respectively.

### exhaustive_calculation_of_fpp.py
This script is designed for the exhaustive calculation of false-positive probability as defined in Definition 8. It should be executed after running **sampling_sequences_AES.cpp** and **sampling_sequences_ARIA**. It is currently configured to calculate the values required for Table 5.

### Exhaustive_Calculation_Result.txt
This file contains the execution results of **exhaustive_calculation_of_fpp.py**.
