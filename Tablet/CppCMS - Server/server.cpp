#include <cppcms/application.h>  
#include <cppcms/service.h>  
#include <cppcms/http_response.h>  
#include <cppcms/url_dispatcher.h>  
#include <cppcms/url_mapper.h>  
#include <cppcms/applications_pool.h>  
#include <iostream>  

#include "logger.h"

//server receives input from site and runs the appropriate methods
class server : public cppcms::application {  
	logger log;

	public:
		server(cppcms::service &srv) : cppcms::application(srv)  
		{  
		    dispatcher().assign("/simon_says",&server::simon_says,this);  
		    mapper().assign("simon_says","/simon_says");  
		  
		    dispatcher().assign("/story",&server::story,this);  
		    mapper().assign("story","/story");  

		    dispatcher().assign("/other",&server::other,this);  
		    mapper().assign("other","/other");  

		    dispatcher().assign("/other2",&server::other2,this);  
		    mapper().assign("other2","/other2");  

		    dispatcher().assign("",&server::welcome,this);  
		    mapper().assign("");  
		  
		    mapper().root("/home");  
		} 

		void simon_says()  
		{  
			log.logEvent("Simon Says");
		  	response().out() << "Running Simon Says Game<br/>\n";  
		    response().out() << "<a href='" << url("/") << "'>Go back</a>";  
		} 

		void story()  
		{  
			log.logEvent("Story");
		  	response().out() << "Telling A Story<br/>\n";  
		    response().out() << "<a href='" << url("/") << "'>Go back</a>";  
		} 

		void other()  
		{  
			log.logEvent("Other 1");
		  	response().out() << "Running Other<br/>\n";  
		    response().out() << "<a href='" << url("/") << "'>Go back</a>";  
		}

		void other2()  
		{  
			log.logEvent("Other 2");
		  	response().out() << "Running Other 2<br/>\n";  
		    response().out() << "<a href='" << url("/") << "'>Go back</a>";  
		}  

		void welcome()  
		{  
		    response().out() <<  
		        "<h1> NAO Tablet Interface </h1>\n"
		        "<br>\n"
		        "<h2> Choose an option: </h2>\n"

		        "<a href='" << url("/story")  << "'>Tell A Story</a><br>\n"  
		        "<a href='" << url("/other") << "' >Other Mode 1</a><br>\n" 
		        "<a href='" << url("/other2") << "' >Other Mode 2</a><br>\n"  
		        "<a href='" << url("/simon_says") << "'>Simon Says</a><br>\n";  
		}  
};

//programs main
int main(int argc,char ** argv)  
{  
    try 
    {  
       	cppcms::service srv(argc,argv);
       	srv.applications_pool().mount(cppcms::applications_factory<server>());
       	srv.run();  
	}

	catch(std::exception const &e) 
	{  
    	std::cerr << e.what() << std::endl;  
	}    
};




