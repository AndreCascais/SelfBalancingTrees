options(scipen = 999)
args = commandArgs(trailingOnly=TRUE)
adds = args[1]
removes = args[2]
lookups = args[3]
a = sample(1:adds, adds)
b = sample(a, removes)
c = sample(setdiff(a, b), lookups)
write(c(0, adds, removes, lookups, a, b, c), file = paste0(adds, 'I', removes, 'R', lookups, 'L.txt'), ncolumns = 1, sep = " ")