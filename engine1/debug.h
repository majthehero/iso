#pragma once

#define DEBUG

#ifdef DEBUG
#define LOG( F )  std::cerr << F << std::endl 
#else
#define LOG( F ) ;;
#endif