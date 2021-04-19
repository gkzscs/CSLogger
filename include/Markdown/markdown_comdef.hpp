#ifndef MARKDOWN_COMDEF_HPP
#define MARKDOWN_COMDEF_HPP

#include <QString>


namespace markdown
{

#define DEF_SC_STR  static const QString


/************************************* Markdown Syntax *****************************************/
// Basci symbol
DEF_SC_STR scTab = "\t";
DEF_SC_STR scNextLine = "\n";

// Title
DEF_SC_STR scTitle_1 = "# ";
DEF_SC_STR scTitle_2 = "## ";
DEF_SC_STR scTitle_3 = "### ";
DEF_SC_STR scTitle_4 = "#### ";
DEF_SC_STR scTitle_5 = "##### ";
DEF_SC_STR scTitle_6 = "###### ";

// Paragraph format
DEF_SC_STR scBoldPart = "**";
DEF_SC_STR scItalicPart = "_";
DEF_SC_STR scBoldItalicPart = "***";
DEF_SC_STR scSplitLine = "---";
DEF_SC_STR scStrikeOutPart = "~~";
DEF_SC_STR scUnderLineLeft = "<u>";
DEF_SC_STR scUnderLineRight = "</u>";
DEF_SC_STR scFooterLeft = "[^";
DEF_SC_STR scFooterRight = "]";

// List
DEF_SC_STR scUnorderedList = "- ";
DEF_SC_STR scOrderedList = "1. ";

// Block
DEF_SC_STR scBlock_1 = "> ";
DEF_SC_STR scBlock_2 = ">> ";
DEF_SC_STR scBlock_3 = ">>> ";

// Code
DEF_SC_STR scReferencePart = "`";
DEF_SC_STR scCodeLeft = "```\n";
DEF_SC_STR scCodeRight = "\n```";
DEF_SC_STR scCodeCPart = scCodeLeft + "c";
DEF_SC_STR scCodeCppPart = scCodeLeft + "cpp";
DEF_SC_STR scCodeJavaPart = scCodeLeft + "java";
DEF_SC_STR scCodePhpPart = scCodeLeft + "php";
DEF_SC_STR scCodeJsonPart = scCodeLeft + "json";

// Link
DEF_SC_STR scLinkLeft = "<";
DEF_SC_STR scLinkRight = ">";
DEF_SC_STR scNameLinkLeft = "[";
DEF_SC_STR scNameLinkMiddle = "](";
DEF_SC_STR scNameLinkRight = ")";

// Image
DEF_SC_STR scImageLeft = "![";
DEF_SC_STR scImageMiddle = "](";
DEF_SC_STR scImageRight = ")";


}   // End of `markdown`


#endif // MARKDOWN_COMDEF_HPP
