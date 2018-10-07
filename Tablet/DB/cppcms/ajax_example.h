/* 
 * File:   app.h
 * Author: Erasmo
 *
 * Created on 05 de agosto de 2014, 03:34 PM
 */

#ifndef AJAX_EXAMPLE_H
#define	AJAX_EXAMPLE_H

#include "content.h"

#include <cppcms/application.h>
#include <cppcms/service.h>
#include <cppcms/rpc_json.h>
#include <cppcms/url_dispatcher.h>
#include <cppcms/json.h>

#include <string>
#include <iostream>

class AJAX_Example : public cppcms::rpc::json_rpc_server
{
public:
    AJAX_Example(cppcms::service& /* srv */);
    virtual void main(std::string /* url */);
    void load();
    void message();
};

AJAX_Example::AJAX_Example(cppcms::service& srv) : cppcms::rpc::json_rpc_server(srv)
{
    dispatcher().assign("/ajax", &AJAX_Example::load, this);
    mapper().assign("/ajax");
    
    bind("message", cppcms::rpc::json_method(&AJAX_Example::message, this), method_role);
}

void AJAX_Example::main(std::string url)
{
    std::cout << "On main()" << std::endl;
    std::cout << "URL: " << url << std::endl;
    dispatcher().dispatch(url);
}

void AJAX_Example::load()
{
    std::cout << "On load()" << std::endl;
    content::Content c {};
    render("Content", c);
}

void AJAX_Example::message()
{
    std::cout << "On message()" << std::endl;
    return_result("AJAX is cool!");
}

#endif	/* APP_H */

