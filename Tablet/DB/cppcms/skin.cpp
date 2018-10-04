#line 1 "content.tmpl"
#include "content.h" 
#line 2 "content.tmpl"
namespace skin {
	#line 3 "content.tmpl"
	struct Content :public cppcms::base_view
	#line 3 "content.tmpl"
	{
	#line 3 "content.tmpl"
		content::Content &content;
	#line 3 "content.tmpl"
		Content(std::ostream &_s,content::Content &_content): cppcms::base_view(_s),content(_content)
	#line 3 "content.tmpl"
		{
	#line 3 "content.tmpl"
		}
		#line 4 "content.tmpl"
		virtual void render() {
			#line 54 "content.tmpl"
			out()<<"\n"
				"<!DOCTYPE html>\n"
				"<html>\n"
				"    <head>\n"
				"        <title>Ajax Example</title>\n"
				"        <script>\n"
				"            function loadXMLDoc()\n"
				"            {\n"
				"                var xmlhttp = new XMLHttpRequest();\n"
				"                xmlhttp.open(\"POST\", \"/ajax\", true);\n"
				"\n"
				"                xmlhttp.onreadystatechange = function() {\n"
				"                    var res;\n"
				"                    \n"
				"                    if (xmlhttp.readyState === 3) {\n"
				"                        if (xmlhttp.status === 200) {\n"
				"                            var result = eval(\"(\" + xmlhttp.responseText + \")\");\n"
				"\n"
				"                            if (result.error == null) {\n"
				"                                res = result.result;\n"
				"                            }\n"
				"                            else {\n"
				"                                res = result.error;\n"
				"                            }\n"
				"                        }\n"
				"                        else {\n"
				"                            res = \"Invalid Status \" + xmlhttp.status;\n"
				"                        }\n"
				"\n"
				"                        document.getElementById(\"myDiv\").innerHTML = res;\n"
				"                    }\n"
				"                    /*else {\n"
				"                        res = \"Not valid state \" + xmlhttp.readyState;\n"
				"                    }\n"
				"\n"
				"                    document.getElementById(\"myDiv\").innerHTML = res;*/\n"
				"                }\n"
				"\n"
				"                var request = '{\"method\" : \"message\"}';\n"
				"                xmlhttp.send(request);\n"
				"            }\n"
				"        </script>\n"
				"    </head>\n"
				"    <body>\n"
				"        <div id=\"myDiv\">\n"
				"            <h2>Let AJAX change this text</h2>\n"
				"        </div>\n"
				"        <button type=\"button\" onclick=\"loadXMLDoc()\">Change Content</button>\n"
				"    </body>\n"
				"</html>\n"
				"";
		#line 54 "content.tmpl"
		} // end of template render
	#line 55 "content.tmpl"
	}; // end of class Content
#line 56 "content.tmpl"
} // end of namespace skin
#line 56 "content.tmpl"
namespace {
#line 56 "content.tmpl"
 cppcms::views::generator my_generator; 
#line 56 "content.tmpl"
 struct loader { 
#line 56 "content.tmpl"
  loader() { 
#line 56 "content.tmpl"
   my_generator.name("skin");
#line 56 "content.tmpl"
   my_generator.add_view<skin::Content,content::Content>("Content",true);
#line 56 "content.tmpl"
    cppcms::views::pool::instance().add(my_generator);
#line 56 "content.tmpl"
 }
#line 56 "content.tmpl"
 ~loader() {  cppcms::views::pool::instance().remove(my_generator); }
#line 56 "content.tmpl"
} a_loader;
#line 56 "content.tmpl"
} // anon 
