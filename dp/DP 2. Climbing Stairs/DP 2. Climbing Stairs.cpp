int climbStairs(int n) { 
  if( n == 1) return 1;
  if(n == 2) return 2;
  int l = climbStairs(n- 1);
  int r = climbStairs(n-2);
  return l+r;
}
