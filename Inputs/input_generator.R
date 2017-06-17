options(scipen = 999)
args = commandArgs(trailingOnly = TRUE)
adds = args[1]
removes = args[2]
lookups = args[3]
repetitions = args[4]
a = sample(1 : adds, adds)
b = sample(a, removes)
if (repetitions == 0) {
    c = sample(a, lookups)
} else {
    c = sample(a, lookups, replace = TRUE)
}
write(c(0, adds, removes, lookups, a, b, c), file = paste0(adds, 'I', removes, 'R', lookups, 'L.txt'), ncolumns = 1, sep = " ")