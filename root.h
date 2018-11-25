
#ifndef __AQUA__ROOT_H
	#define __AQUA__ROOT_H
	
	typedef signed long long var;
	typedef unsigned long long uvar;
	
	typedef var flt;
	typedef var chr;
	
	typedef uvar uflt;
	typedef uvar uchr;
	
	typedef var device;
	
	#define system platform_system
	#define printf print
	#define sprintf __sprintf
	
	//~ #define NULL ((void*) 0)
	
	// prototypes & __DUMMY_FUNCTION
	
	#include "prototypes.h"
	
	void __DUMMY_FUNCTION(void) {
		print("`%s` in `%s` is a useless dummy function\n", __func__, __FILE__);
		
	}
	
	// threads
	
	var __THREAD_START(var address, var freq, void* argument);
	var __THREAD_FREQ(var address, var freq);
	var __THREAD_END(var address);
	var __THREAD_INST(var address);
	
	// debugging macros
	
	#define BREAK break_point("generic");
	
	// fucc
	
	#define or                        ||
	#define and                       &&
	#define elif                      else if
	#define private                   static
	#define public                    auto
	#define local                     auto
	#define global                    static
	#define arraymin                  static
	#define notnull                   static 1
	#define nooptimizations           volatile
	#define fast                      register
	#define class                     typedef struct
	#define addrof(x)                 (&(x))
	#define deref(x)                  (*(x))
	#define prototype(type, function) type function()
	#define lib(name)                 __lib_function_##name
	#define asm                       __asm__
	#define volatile                  __volatile__
	#define true                      1
	#define false                     0
	#define null                      0
	#define nullptr                   ((void*) null)
	#define pointer                   *
	#define always                    while (true)
	#define macro                     private final var
	#define final                     const
	#define bool                      var
	#define packed                    __attribute__((packed))
	#define unused                    __attribute__((unused))
	#define weak                      __attribute__((weak))
	#define iterate(max)              for (var i = 0; i < max; i++)
	#define then                      ?
	#define orelse                    :
	#define not                       !
	#define no                        not
	
	#define new(   class_name, ...)          new_##class_name((class_name##_t*) malloc(sizeof(class_name##_t*)), __VA_ARGS__)
    #define delete(class_name, object) { dispose_##class_name(object); mfree(object,   sizeof(typeof(object))); }
	
	/// TODO inline asm
	
	//~ #define div(x, y) ({var result; __asm__ __volatile__ ("mov %%rax, %1\n\tdiv $2, %%rax\n\tmov %0, %%rax" : "=g" (result) : "g" (x) : "rax"); result;})
	//~ #define mul(x, y) ({var result; __asm__ __volatile__ ("mul %%rax, %1\n" :: "g" (x), "g" (y) : "rax"); result;})
	
#endif
