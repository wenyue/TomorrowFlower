#pragma once

#ifdef _USRDLL
#define TF_DLL		__declspec(dllexport)
#else
#define TF_DLL		__declspec(dllimport)
#endif

#define SUPER(SUPER_NAME) public: typedef SUPER_NAME Super;

#define PORPERTY(TYPE, PORPERTY_NAME)			\
PORPERTY_GET(TYPE, PORPERTY_NAME)				\
PORPERTY_SET(TYPE, PORPERTY_NAME)

#define PORPERTY_GET(TYPE, PORPERTY_NAME)		\
virtual TYPE get##PORPERTY_NAME() = 0;

#define PORPERTY_SET(TYPE, PORPERTY_NAME)		\
virtual void set##PORPERTY_NAME(const TYPE &value) = 0;

#define MEMBER(TYPE, PORPERTY_NAME)					\
public: TYPE get##PORPERTY_NAME()					\
{ return m##PORPERTY_NAME; }						\
public: void set##PORPERTY_NAME(const TYPE &value)	\
{ m##PORPERTY_NAME = value; }						\
private: TYPE m##PORPERTY_NAME;

#define MEMBER_GET(TYPE, PORPERTY_NAME)				\
public: TYPE get##PORPERTY_NAME()					\
{ return m##PORPERTY_NAME; }						\
private: TYPE m##PORPERTY_NAME;

#define MEMBER_SET(TYPE, PORPERTY_NAME)				\
public: void set##PORPERTY_NAME(const TYPE &value)	\
{ m##PORPERTY_NAME = value; }						\
private: TYPE m##PORPERTY_NAME;