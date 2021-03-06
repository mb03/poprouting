/*
 * graph_parser_wrapper.cpp
 *
 *  Created on: 10 mag 2016
 *      Author: gabriel
 */


#include "graph_parser_wrapper.h"
#include "graph_parser.h"


struct membuf : std::streambuf
{
    membuf(char* begin, char* end) {
        this->setg(begin, begin, end);
    }
};



extern "C" {
		c_graph_parser* new_graph_parser(int weight, int heuristic){
    		graph_parser *v = (graph_parser*)new graph_parser(weight, heuristic);
    		return (c_graph_parser *)v;
        }

        void graph_parser_parse_netjson(c_graph_parser* v, char *json){
        		graph_parser *vc = (graph_parser*)v;
            	membuf sbuf(json, json + sizeof(json));
                std::istream in(&sbuf);
                vc->_parse_netjson(in);
        }

        void graph_parser_parse_jsoninfo(c_graph_parser* v, char *json){
    		graph_parser *vc = (graph_parser*)v;

        	membuf sbuf(json, json + sizeof(json));
                std::istream in(&sbuf);
                vc->_parse_jsoinfo(in);
        }

        void graph_parser_calculate_bc(c_graph_parser* v){
    		graph_parser *vc = (graph_parser*)v;
        	vc->calculate_bc();
        }

        void graph_parser_compose_bc_map(c_graph_parser* v, id_bc_pair * map){
    		graph_parser *vc = (graph_parser*)v;
        	vector<pair<string, double> > cppmap;
        	vc->compose_bc_map(cppmap);

        	int i=0;
        	//id_bc_pair *c_map = (id_bc_pair*)malloc(sizeof(id_bc_pair)*cppmap.size());
        	//id_bc_pair *c_map = new id_bc_pair[cppmap.size()];
        	//for(pair<string, double> item: cppmap){
        	//	c_map[i].id = new char[item.first.length()];
        	//	strcpy(c_map[i].id, item.first.c_str());
        	//	c_map[i++].bc = item.second;
        	//}
        	//map = c_map;
        }


        void delete_my_class(c_graph_parser* v) {
    		graph_parser *vc = (graph_parser*)v;
        	delete vc;
        }
}

