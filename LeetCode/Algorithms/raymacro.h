#ifndef RAYMACRO_H
#define RAYMACRO_H

// This is used as my own debug output. I need to set RAYDEBUG=false/true
static bool RAYDEBUG=false;
#define RCOUT if(RAYDEBUG) cout 

#define RDEBUG(x) cout << '>' << #x << ':' << x << '\n';
//#define THROW_IF(val) if (val) throw "error in " __FUNCTION__
#define RBARK cout << __FUNCTION__ << '\n';



#endif



