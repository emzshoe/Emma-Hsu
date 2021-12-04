# Examining whether each of the ratios appear normally distributes by making histograms
# and superposing normal densities and then making probability plots
isotopeData = read.csv('potassium.txt', sep = ",")
num = 78
col1 = vector(mode = "numeric", length = num)
col2 = vector(mode = "numeric", length = num)

for (i in 1:num){
  col1[i] = isotopeData$X.K39.41.[i]
  col2[i] = isotopeData$X.K41.40.[i]
}

col1.mean = mean(col1)
col1.var = var(col1)
col2.mean = mean(col2)
col2.var = var(col2)

#39K/41K
x1.plot = seq(13.5, 14.0, length.out=500)
hist(col1, breaks = seq(from = 13.84, to = 13.88, by = 0.003), freq = FALSE, main = '39K/41K')
lines(x1.plot, dnorm(x1.plot, mean = col1.mean, sd = sqrt(col1.var)), col = 'purple')

qqnorm(col1, main = "39K/41K", xlab = "Quantiles", ylab = "Observations", cex = .75)
qqline(col1, distribution = qnorm, col = "purple")


# 41K/40K
x2.plot = seq(570, 585, length.out=500)
hist(col2, breaks = seq(from = 573, to = 581, by = 1), freq = FALSE, main = '41K/40K')
lines(x2.plot, dnorm(x2.plot, mean = col2.mean, sd = sqrt(col2.var)), col = 'red')

qqnorm(col2, main = "41K/40K", xlab = "Quantiles", ylab = "Observations", cex = .75)
qqline(col2, distribution = qnorm, col = "red")