#include <iostream>
#include "pugixml.hpp"

using namespace std;

void check_xml(const char* source) {
// tag::code[]
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_string(source);

	if (result) {
		std::cout << "XML [" << source
				<< "] parsed without errors, attr value: ["
				<< doc.child("node").attribute("attr").value() << "]\n\n";
	} else {
		std::cout << "XML [" << source << "] parsed with errors, attr value: ["
				<< doc.child("node").attribute("attr").value() << "]\n";
		std::cout << "Error description: " << result.description() << "\n";
		std::cout << "Error offset: " << result.offset << " (error at [..."
				<< (source + result.offset) << "]\n\n";
	}
// end::code[]
}
int main1() {


	/* // Load document
	 pugi::xml_document doc;

	 pugi::xml_parse_result result = doc.load_file("tree.xml");

	 std::cout << "Load result: " << result.description() << ", mesh name: "
	 << doc.child("mesh").attribute("name").value() << std::endl;
	 // end Load document*/

	/*
	 // load error handling
	 check_xml("<node attr='value'><child>text</child></node>");
	 check_xml("<node attr='value'><child>text</chil></node>");
	 check_xml("<node attr='value'><child>text</child>");
	 check_xml("<node attr='value\"><child>text</child></node>");
	 check_xml("<node attr='value'><#tag /></node>");
	 // end load error handling

	 */

/*
	// traverse
	pugi::xml_document doc;
	if (!doc.load_file("xgconsole.xml"))
		return -1;

	pugi::xml_node tools = doc.child("Profile").child("Tools");
*/
	/*
	// tag::basic[]
	for (pugi::xml_node tool = tools.first_child(); tool;
			tool = tool.next_sibling()) {
		std::cout << "Tool:";

		for (pugi::xml_attribute attr = tool.first_attribute(); attr;
				attr = attr.next_attribute()) {
			std::cout << " " << attr.name() << "=" << attr.value();
		}

		std::cout << std::endl;
	}
	// end::basic[]

	std::cout << std::endl;

	// tag::data[]
	for (pugi::xml_node tool = tools.child("Tool"); tool;
			tool = tool.next_sibling("Tool")) {
		std::cout << "Tool " << tool.attribute("Filename").value();
		std::cout << ": AllowRemote "
				<< tool.attribute("AllowRemote").as_bool();
		std::cout << ", Timeout " << tool.attribute("Timeout").as_int();
		std::cout << ", Description '" << tool.child_value("Description")
				<< "'\n";
		// object creation
		// add to vector/map
	}
	// end::data[]

	std::cout << std::endl;
*/
	/*

	// finding a node/attribute with the correct name
	// tag::contents[]
	std::cout << "Tool for *.dae generation: "
			<< tools.find_child_by_attribute("Tool", "OutputFileMasks", "*.dae").attribute(
					"Filename").value() << "\n";

	for (pugi::xml_node tool = tools.child("Tool"); tool;
			tool = tool.next_sibling("Tool")) {
		std::cout << "Tool " << tool.attribute("Filename").value() << "\n";
	}
	// end::contents[]
*/
/*
	 //modify
	 pugi::xml_document doc;
	 if (!doc.load_string("<node id='123'>text</node><!-- comment -->",
			 pugi::parse_default | pugi::parse_comments))
	 return -1;

	 // tag::node[]
	 pugi::xml_node node = doc.child("node");

	 // change node name
	 std::cout << node.set_name("notnode");
	 std::cout << ", new node name: " << node.name() << std::endl;

	 // change comment text
	 std::cout << doc.last_child().set_value("useless comment");
	 std::cout << ", new comment text: " << doc.last_child().value()
	 << std::endl;

	 // we can't change value of the element or name of the comment
	 std::cout << node.set_value("1") << ", " << doc.last_child().set_name("2")
	 << std::endl;
	 // end::node[]

	 // tag::attr[]
	 pugi::xml_attribute attr = node.attribute("id");

	 // change attribute name/value
	 std::cout << attr.set_name("key") << ", " << attr.set_value("345");
	 std::cout << ", new attribute: " << attr.name() << "=" << attr.value()
	 << std::endl;

	 // we can use numbers or booleans
	 attr.set_value(1.234);
	 std::cout << "new attribute value: " << attr.value() << std::endl;

	 // we can also use assignment operators for more concise code
	 attr = true;
	 std::cout << "final attribute value: " << attr.value() << std::endl;
	 // end::attr[]

*/

/*
	 // add new attributes/nodes
	 pugi::xml_document doc;

	 // tag::code[]
	 // add node with some name
	 pugi::xml_node node = doc.append_child("node");

	 // add description node with text child
	 pugi::xml_node descr = node.append_child("description");
	 descr.append_child(pugi::node_pcdata).set_value("Simple node");

	 // add param node before the description
	 pugi::xml_node param = node.insert_child_before("param", descr);

	 // add attributes to param node
	 param.append_attribute("name") = "version";
	 param.append_attribute("value") = 1.1;
	 param.insert_attribute_after("type", param.attribute("name")) = "float";
	 // end::code[]

	 doc.print(std::cout);
*/

/*
	 // save to file
	 // get a test document
	 pugi::xml_document doc;
	 doc.load_string("<foo bar='baz'>hey</foo>");

	 // tag::code[]
	 // save document to file
	 std::cout << "Saving result: " << doc.save_file("save_file_output.xml")
	 << std::endl;
	 // end::code[]
*/

	/*
	 // save to std
	 // get a test document
	 pugi::xml_document doc;
	 doc.load_string("<foo bar='baz'><call>hey</call></foo>");

	 // tag::code[]
	 // save document to standard output
	 std::cout << "Document:\n";
	 doc.save(std::cout);
	 // end::code[]
	 */
	return 0;
}
