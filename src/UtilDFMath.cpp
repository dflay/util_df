#include "UtilDFMath.hh"
//______________________________________________________________________________
namespace util_df{
   namespace Math{
      //______________________________________________________________________________
      double SimpsonIntegral(double (*f)(const double),
	    double A,double B,double epsilon,int Depth){
	 // Adaptive Simpson's Rule
	 double C   = (A + B)/2.0;
	 double H   = B - A;
	 double fa  = (*f)(A);
	 double fb  = (*f)(B);
	 double fc  = (*f)(C);
	 double S   = (H/6.0)*(fa + 4.0*fc + fb);
	 double ans = AdaptiveSimpsonAux(f,A,B,epsilon,S,fa,fb,fc,Depth);
	 return ans;
      }
      //______________________________________________________________________________
      double AdaptiveSimpsonAux(double (*f)(const double),
	    double A,double B,double epsilon,
	    double S,double fa,double fb,double fc,int bottom){
	 // Recursive auxiliary function for AdaptiveSimpson() function
	 double C      = (A + B)/2.0;
	 double H      = B - A;
	 double D      = (A + C)/2.0;
	 double E      = (C + B)/2.0;
	 double fd     = (*f)(D);
	 double fe     = (*f)(E);
	 double Sleft  = (H/12.0)*(fa + 4.0*fd + fc);
	 double Sright = (H/12.0)*(fc + 4.0*fe + fb);
	 double S2     = Sleft + Sright;
	 if( (bottom <= 0) || (fabs(S2 - S) <= 15.0*epsilon) ){
	    return S2 + (S2 - S)/15;
	 }
	 double arg = AdaptiveSimpsonAux(f,A,C,epsilon/2.0,Sleft, fa,fc,fd,bottom-1) +
	    AdaptiveSimpsonAux(f,C,B,epsilon/2.0,Sright,fc,fb,fe,bottom-1);
	 return arg;
      }
      //______________________________________________________________________________
      int LeastSquaresFitting(std::vector<double> x,std::vector<double> y,double &intercept,double &slope,double &r){
	 // we do this just in case we need to loop over N < x.size() 

	 // linear regression to find slope b and y-intercept a of 
	 // f(x) = a + bx 

	 int rc=0;
	 double num=0,rsq=0;

	 const int N   = x.size();
	 double mean_x = GetMean<double>(x);
	 double mean_y = GetMean<double>(y);
	 double var_x  = GetVariance<double>(x);
	 double var_y  = GetVariance<double>(y);
	 double cov_xy = GetCovariance<double>(x,y);

	 double ss_xx = ( (double)N )*var_x;
	 double ss_yy = ( (double)N )*var_y;
	 double ss_xy = ( (double)N )*cov_xy;

	 double den = ss_xx*ss_yy;
	 if(den==0){
	    // singular matrix. can't solve the problem.
	    intercept = 0;
	    slope     = 0;
	    r         = 0;
	    rc        = 1;
	 }else{
	    slope     = cov_xy/var_x;
	    intercept = mean_y - slope*mean_x;
	    num       = ss_xy*ss_xy;
	    rsq       = num/den;
	    r         = sqrt(rsq);
	 }
	 return rc;
      }
      //______________________________________________________________________________
      int LeastSquaresFitting(int N,double *x,double *y,double &intercept,double &slope,double &r){
	 // we do this just in case we need to loop over N < x.size() 

	 // linear regression to find slope b and y-intercept a of 
	 // f(x) = a + bx 

	 int rc=0;
	 double num=0,rsq=0;

	 double mean_x = GetMean<double>(N,x);
	 double mean_y = GetMean<double>(N,y);
	 double var_x  = GetVariance<double>(N,x);
	 double var_y  = GetVariance<double>(N,y);
	 double cov_xy = GetCovariance<double>(N,x,y);

	 double ss_xx = ( (double)N )*var_x;
	 double ss_yy = ( (double)N )*var_y;
	 double ss_xy = ( (double)N )*cov_xy;

	 double den = ss_xx*ss_yy;
	 if(den==0){
	    // singular matrix. can't solve the problem.
	    intercept = 0;
	    slope     = 0;
	    r         = 0;
	    rc        = 1;
	 }else{
	    slope     = cov_xy/var_x;
	    intercept = mean_y - slope*mean_x;
	    num       = ss_xy*ss_xy;
	    rsq       = num/den;
	    r         = sqrt(rsq);
	 }
	 return rc;
      }
      //______________________________________________________________________________
      double LinearInterpolation(double x,double x0,double y0,double x1,double y1){
	 double b = (x-x0)/(x1-x0);
	 double y = y0 + b*(y1-y0);
	 return y;
      }
      //______________________________________________________________________________
      double AllanVariance(std::vector<double> x, const int M){
         // compute the allan variance for M points per group 
         // in the data vector x of size N points.
 
         const int N = x.size();

         double sum_sq=0,mean=0,mean_prev=0,diff=0;
         double v[M]; 

         int nAVG=0,j=0;
         for(int i=1;i<N+1;i++){
	    v[j] = x[i-1];  
            if(i%M==0){
	       // got the number of points we need, compute average 
	       nAVG++;
               mean = GetMean<double>(M,v);
               diff = mean-mean_prev;
               // sum over squared differences for nAVG>1 
	       if(nAVG>1) sum_sq += pow(diff,2.); 
               // reset the j index and mean_prev now that we computed an average 
	       j = 0;
	       mean_prev = mean; 
            }else{
	       // keep going
	       j++;
            }
         }

         // now get the variance 
         double allanVar = sum_sq/( 2.*(nAVG-1) );
	 return allanVar;
      }
      //______________________________________________________________________________
      double AllanDeviation(std::vector<double> x, const int M){
         // compute the allan deviation for M points per group 
         // in the data vector x of size N points.
         double allanVar = AllanVariance(x,M); 
         double allanDev = sqrt(allanVar); 
	 return allanDev;
      }
   } // ::Math 
} // ::util_df

