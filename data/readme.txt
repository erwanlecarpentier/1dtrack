# Backup path

Code explanation for the data file (.csv files) saved in this repository.
The saved files follow the syntax written below:

{POLICY_SELECTOR}_{TRACK_LEN}_{STDDEV}_{FAILURE_PROBABILITY}_{BUDGET}_{HORIZON}_...
{UCT_CST}_{DISCOUNT_FACTOR}_{EPSILON}_{MODEL_TRACK_LEN}_{MODEL_STDDEV}_...
{MODEL_FAILURE_PROBABILITY}.csv

For instance, with the parameters written below, the file would be named:
1_2_020_005_15_5_070_1_010_2_020_005.csv

POLICY_SELECTOR = 1
TRACK_LEN = 2.0
STDDEV = 0.2
FAILURE_PROBABILITY = 0.05
BUDGET = 15
HORIZON = 5
UCT_CST = 0.7
DISCOUNT_FACTOR = 1.0
EPSILON = 0.1
MODEL_TRACK_LEN = 2.0
MODEL_STDDEV = 0.2
MODEL_FAILURE_PROBABILITY = 0.05

# Notes

Double variables are made integer.
No negative values.
Double below 0. are multiplied by 100 and made integer. Zeros are added so
that we keep track of the order of magnitude.

