#include <node_api.h>
#include "jsfeature_top.hpp"
#include "utils.hpp"
extern template napi_value top_<int64_t,int64_t,int64_t,true,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,int64_t,js_array<int64_t>,true,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,int64_t,int64_t,false,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,int64_t,js_array<int64_t>,false,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,int64_t,int32_t,true,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,int64_t,js_array<int32_t>,true,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,int64_t,int32_t,false,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,int64_t,js_array<int32_t>,false,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,int64_t,bool,true,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,int64_t,js_array<bool>,true,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,int64_t,bool,false,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,int64_t,js_array<bool>,false,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,int64_t,double,true,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,int64_t,js_array<double>,true,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,int64_t,double,false,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,int64_t,js_array<double>,false,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,int64_t,std::string,true,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,int64_t,js_array<std::string>,true,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,int64_t,std::string,false,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,int64_t,js_array<std::string>,false,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,int64_t,uint64_t,true,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,int64_t,js_array<uint64_t>,true,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,int64_t,uint64_t,false,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,int64_t,js_array<uint64_t>,false,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,int32_t,int64_t,true,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,int32_t,js_array<int64_t>,true,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,int32_t,int64_t,false,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,int32_t,js_array<int64_t>,false,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,int32_t,int32_t,true,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,int32_t,js_array<int32_t>,true,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,int32_t,int32_t,false,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,int32_t,js_array<int32_t>,false,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,int32_t,bool,true,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,int32_t,js_array<bool>,true,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,int32_t,bool,false,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,int32_t,js_array<bool>,false,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,int32_t,double,true,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,int32_t,js_array<double>,true,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,int32_t,double,false,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,int32_t,js_array<double>,false,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,int32_t,std::string,true,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,int32_t,js_array<std::string>,true,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,int32_t,std::string,false,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,int32_t,js_array<std::string>,false,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,int32_t,uint64_t,true,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,int32_t,js_array<uint64_t>,true,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,int32_t,uint64_t,false,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,int32_t,js_array<uint64_t>,false,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,bool,int64_t,true,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,bool,js_array<int64_t>,true,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,bool,int64_t,false,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,bool,js_array<int64_t>,false,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,bool,int32_t,true,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,bool,js_array<int32_t>,true,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,bool,int32_t,false,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,bool,js_array<int32_t>,false,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,bool,bool,true,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,bool,js_array<bool>,true,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,bool,bool,false,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,bool,js_array<bool>,false,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,bool,double,true,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,bool,js_array<double>,true,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,bool,double,false,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,bool,js_array<double>,false,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,bool,std::string,true,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,bool,js_array<std::string>,true,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,bool,std::string,false,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,bool,js_array<std::string>,false,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,bool,uint64_t,true,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,bool,js_array<uint64_t>,true,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,bool,uint64_t,false,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,bool,js_array<uint64_t>,false,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,double,int64_t,true,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,double,js_array<int64_t>,true,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,double,int64_t,false,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,double,js_array<int64_t>,false,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,double,int32_t,true,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,double,js_array<int32_t>,true,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,double,int32_t,false,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,double,js_array<int32_t>,false,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,double,bool,true,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,double,js_array<bool>,true,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,double,bool,false,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,double,js_array<bool>,false,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,double,double,true,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,double,js_array<double>,true,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,double,double,false,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,double,js_array<double>,false,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,double,std::string,true,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,double,js_array<std::string>,true,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,double,std::string,false,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,double,js_array<std::string>,false,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,double,uint64_t,true,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,double,js_array<uint64_t>,true,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,double,uint64_t,false,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,double,js_array<uint64_t>,false,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,std::string,int64_t,true,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,std::string,js_array<int64_t>,true,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,std::string,int64_t,false,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,std::string,js_array<int64_t>,false,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,std::string,int32_t,true,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,std::string,js_array<int32_t>,true,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,std::string,int32_t,false,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,std::string,js_array<int32_t>,false,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,std::string,bool,true,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,std::string,js_array<bool>,true,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,std::string,bool,false,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,std::string,js_array<bool>,false,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,std::string,double,true,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,std::string,js_array<double>,true,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,std::string,double,false,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,std::string,js_array<double>,false,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,std::string,std::string,true,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,std::string,js_array<std::string>,true,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,std::string,std::string,false,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,std::string,js_array<std::string>,false,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,std::string,uint64_t,true,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,std::string,js_array<uint64_t>,true,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,std::string,uint64_t,false,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,std::string,js_array<uint64_t>,false,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,uint64_t,int64_t,true,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,uint64_t,js_array<int64_t>,true,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,uint64_t,int64_t,false,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,uint64_t,js_array<int64_t>,false,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,uint64_t,int32_t,true,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,uint64_t,js_array<int32_t>,true,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,uint64_t,int32_t,false,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,uint64_t,js_array<int32_t>,false,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,uint64_t,bool,true,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,uint64_t,js_array<bool>,true,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,uint64_t,bool,false,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,uint64_t,js_array<bool>,false,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,uint64_t,double,true,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,uint64_t,js_array<double>,true,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,uint64_t,double,false,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,uint64_t,js_array<double>,false,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,uint64_t,std::string,true,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,uint64_t,js_array<std::string>,true,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,uint64_t,std::string,false,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,uint64_t,js_array<std::string>,false,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,uint64_t,uint64_t,true,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,uint64_t,js_array<uint64_t>,true,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,uint64_t,uint64_t,false,cross::non_iterable>(napi_env env, js_function & jsf, jsfeature * obj);
extern template napi_value top_<int64_t,uint64_t,js_array<uint64_t>,false,cross::iterable>(napi_env env, js_function & jsf, jsfeature * obj);
