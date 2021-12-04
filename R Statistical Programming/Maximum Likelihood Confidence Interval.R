# Constructing a confidence interval from an MLE using a probability distribution pivot

# Initializing given info
n=25
x.bar=24.9
alpha=.1

# MLE-based CI
z.val=qnorm(p=1-alpha/2)
norm.lo=x.bar-z.val*sqrt(x.bar/n)
norm.hi=x.bar+z.val*sqrt(x.bar/n)
cat("Norm approx CI = (",round(norm.lo,2), ",", round(norm.hi,2),")","\n", sep="")

sum.x=n*x.bar
pivot.lo=qchisq(p=alpha/2, df=2*sum.x)/(2*n)
pivot.hi=qchisq(p=1-alpha/2, df=2*(sum.x+1))/(2*n)
cat("Pivoting c.d.f. CI = (",round(pivot.lo,2), ",", round(pivot.hi,2),")","\n", sep="")

# coverage probability plots
n.plot=100
l.plot=seq(.0001,1,length.out=n.plot)
B=10000
cp.norm=vector(mode="numeric", length=n.plot)
cp.pivot=vector(mode="numeric", length=n.plot)
for (i in 1:n.plot) {
  sim.sum=runif(n, min = 0, max = l.plot[i])
  norm.log= (abs(sim.sum/n-l.plot[i]) <= z.val*sqrt(sim.sum/n^2)) # vec of T/F's
  cp.norm[i] = sum(norm.log)/B  # fraction of times norm CI captured lambda = l.plot[i]
  ci.lo=qchisq(p=alpha/2, df=2*sim.sum)/(2*n)
  ci.hi=qchisq(p=1-alpha/2, df=2*(sim.sum+1))/(2*n)
  cp.pivot[i] = sum((l.plot[i] <= ci.hi)&(l.plot[i]>=ci.lo))/B
}

plot(x=l.plot, y=cp.pivot, type="l", ylim=c(0,1), xlab="lambda", ylab="Cov prob")
abline(h=1-alpha,col="red")
lines(x=l.plot, y=cp.norm, col="purple")