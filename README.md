# Accurate False-positive Probability of Multiset-based Demirci-Selçuk Meet-in-the-middle Attacks

This repository contains codes for accurately calculating the false-positive probability and conducting toy experiments for the paper titled "Accurate False-positive Probability of Multiset-based Demirci-Selçuk Meet-in-the-middle Attacks."

## Contents

- **accurate_calculation_of_fpp.py:** This script provides the function to calculate the accurate false-positive probability given parameters N, u, v (= delta(1, N, u, v)). Now it is written calculating the values in Table 3 and 4.
- **Accurate_Calculation_Results.txt:** Execution result of **accurate_calculation_of_fpp.py**.

- **sampling_sequences_AES.cpp, sampling_sequences_ARIA:** These scripts are for sampling sequences. Execution of these codes will output the text file named **Sampling_Result_AES.txt** and **Sampling_Result_ARIA.txt**, respectively.
- **exhaustive_calculation_of_fpp.py:** This script is for exhaustive calculation of false-positive probability as defined in Definition 8. It should be excuted after excution of **sampling_sequences_AES.cpp** and **sampling_sequences_ARIA:**. Now it is written calculating the values in Table 5.
- **Exhaustive_Calculation_Result.txt:** Execution result of **exhaustive_calculation_of_fpp.py**.
