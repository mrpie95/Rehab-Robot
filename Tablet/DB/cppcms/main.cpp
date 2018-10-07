/* 
 * File:   main.cpp
 * Author: Erasmo
 *
 * Created on 03 de agosto de 2014, 11:23 PM
 */

#include "ajax_example.h"

#include <cppcms/application.h>
#include <cppcms/applications_pool.h>
#include <cppcms/service.h>
#include <cppcms/http_response.h>
#include <iostream>

/*
 * 
 */
int main(int argc, char** argv)
{
    try {
        cppcms::service srv {argc, argv};
        srv.applications_pool().mount(
                cppcms::applications_factory<conn.php>()
        );
        std::cout << "Service started." << std::endl;
        srv.run();
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}

