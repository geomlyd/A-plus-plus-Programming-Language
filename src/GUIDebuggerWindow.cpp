#include "GUIDebuggerWindow.h"
#include <sstream>
#include <iostream>

GUIDebuggerWindow::GUIDebuggerWindow(){
    this->set_default_size(1200, 768);
    this->set_border_width(10);
    
    masterGrid = Gtk::Grid();
    buttonBox = Gtk::Box(Gtk::ORIENTATION_VERTICAL);
    breakPointBox = Gtk::Box(Gtk::ORIENTATION_VERTICAL);
    selection = callStackView.get_selection();   
    variablesDisplay = Gtk::TreeView();
    callStackView =  Gtk::TreeView();
    continueButton = Gtk::Button("Continue ");    
    stepOverButton = Gtk::Button("Step over ");
    stepInButton = Gtk::Button("Step in ");
    clearAllBreakpointsButton = Gtk::Button("Clear all breakpoints ");

    continueButton.set_always_show_image(true);   
    continueButton.set_image_from_icon_name("media-playback-start", Gtk::BuiltinIconSize::ICON_SIZE_BUTTON);
    continueButton.set_image_position(Gtk::PositionType::POS_RIGHT);

    stepOverButton.set_always_show_image(true);   
    stepOverButton.set_image_from_icon_name("go-last", Gtk::BuiltinIconSize::ICON_SIZE_BUTTON);
    stepOverButton.set_image_position(Gtk::PositionType::POS_RIGHT); 

    stepInButton.set_always_show_image(true);   
    stepInButton.set_image_from_icon_name("go-down", Gtk::BuiltinIconSize::ICON_SIZE_BUTTON);
    stepInButton.set_image_position(Gtk::PositionType::POS_RIGHT);    

    clearAllBreakpointsButton.set_always_show_image(true);   
    clearAllBreakpointsButton.set_image_from_icon_name("edit-clear", Gtk::BuiltinIconSize::ICON_SIZE_BUTTON);
    clearAllBreakpointsButton.set_image_position(Gtk::PositionType::POS_RIGHT); 

    buttonBox.pack_start(continueButton); 
    buttonBox.pack_start(stepInButton);
    buttonBox.pack_start(stepOverButton);
    buttonBox.pack_start(clearAllBreakpointsButton);

    addBreakPointButton = Gtk::Button("Add Breakpoint");
    removeBreakPointButton = Gtk::Button("Remove Breakpoint");
    
    breakPointEntry.set_max_length(10);
    
    breakPointBox.add(innerBreakPointEntryBox);
    breakPointBox.add(innerBreakPointButtonsBox);
    innerBreakPointEntryBox.pack_start(breakPointEntry);
    innerBreakPointButtonsBox.pack_start(addBreakPointButton);
    innerBreakPointButtonsBox.pack_start(removeBreakPointButton);    

    variablesDisplayEntries = Gtk::TreeStore::create(varDispColumnns);
    variablesDisplay.set_model(variablesDisplayEntries);   
    variablesDisplay.append_column("Variable name", varDispColumnns.variableNameColumn);
    variablesDisplay.append_column("Value", varDispColumnns.variableValueColumn);
    variablesContainer = Gtk::ScrolledWindow();
    variablesContainer.add(variablesDisplay);

    callStackEntries = Gtk::ListStore::create(callStackDispColumns);
    callStackView.set_model(callStackEntries);   
    callStackView.append_column("Call Line Number", callStackDispColumns.functionCallID);      
    callStackContainer = Gtk::ScrolledWindow();
    callStackContainer.add(callStackView);

    m_ScrolledWindow = Gtk::ScrolledWindow();
    m_ScrolledWindow2 = Gtk::ScrolledWindow();

    codeContainerFrame = Gtk::Frame("Source file");
    codeContainerFrame2 = Gtk::Frame("Source file, meta expressions evaluated");
    m_TextView.set_editable(false);
    m_TextView2.set_editable(false);
    m_ScrolledWindow.add(m_TextView);
    m_ScrolledWindow2.add(m_TextView2);
    m_ScrolledWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    m_ScrolledWindow2.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    codeContainerFrame.add(m_ScrolledWindow);
    codeContainerFrame2.add(m_ScrolledWindow2);
    Glib::RefPtr<Gtk::TextTag> highlightTag;
    m_refTextBuffer = Gtk::TextBuffer::create();
    m_refTextBuffer2 = Gtk::TextBuffer::create();
    highlightTag = m_refTextBuffer->create_tag("backgroundColor");
    highlightTag->set_property("background", std::string("orange"));
    tags.push_back(highlightTag);
    highlightTag = m_refTextBuffer2->create_tag("backgroundColor");
    highlightTag->set_property("background", std::string("orange"));
    tags2.push_back(highlightTag);   

    masterGrid.set_row_homogeneous(true);
    masterGrid.set_column_homogeneous(true);
    masterGrid.attach(buttonBox, 0, 0, 1, 1);
    masterGrid.attach(breakPointBox, 0, 1, 1, 1);
    masterGrid.attach(variablesContainer, 0, 2, 2, 3);
    masterGrid.attach(callStackContainer, 1, 0, 1, 2);
    masterGrid.attach(codeContainerFrame, 2, 0, 2, 5);
    masterGrid.attach(codeContainerFrame2, 4, 0, 2, 5);
    this->add(masterGrid);
    this->show_all_children();
}

void GUIDebuggerWindow::addVariableRow(std::string name, std::string value) {
    lastRowInserted = *(variablesDisplayEntries->append());
    lastRowInserted[varDispColumnns.variableNameColumn] = name;
    lastRowInserted[varDispColumnns.variableValueColumn] = value;   
}

void GUIDebuggerWindow::addVariableChildRow(std::string name, std::string value) {
    st.push(lastRowInserted);
    lastRowInserted = *(variablesDisplayEntries->append(lastRowInserted.children()));
    lastRowInserted[varDispColumnns.variableNameColumn] = name;
    lastRowInserted[varDispColumnns.variableValueColumn] = value;   
}

void GUIDebuggerWindow::popOut() {
    if (st.empty())
        throw std::runtime_error("wtf man");
    lastRowInserted = st.top();
    st.pop();
}

void GUIDebuggerWindow::clearVariables() {
    st.empty();
    variablesDisplayEntries->clear();
}

int GUIDebuggerWindow::getBreakPointValueFromEntry() {
    std::string str = breakPointEntry.get_text();

    if (str.length() == 0)
        return 0;
    else
        return atoi(str.c_str());
}


void GUIDebuggerWindow::fillBuffer(std::string code, int buffer) {
    if (buffer == 0) src1 = code;
    else src2 = code;
    updateBuffer(0, buffer);
}

void GUIDebuggerWindow::updateBuffer(int line, int buffer) {
    auto curSrc = (buffer == 0 ? src1 : src2);
    std::stringstream ss(curSrc);
    std::string to;
    int counter = 0;
    auto curBuffer = (buffer == 0 ? m_refTextBuffer : m_refTextBuffer2);
    curBuffer->set_text("");
    Gtk::TextIter iter;
    iter = curBuffer->end();

    int line_actual;
    if (line < 0) line_actual = lastHighlightedLine;
    else line_actual = line;
    while (std::getline(ss, to, '\n')) {
        counter++;
        if (counter == line_actual) {
            if (brlines.find(counter) != brlines.end()) curBuffer->insert_with_tags(iter, "●  "+ std::to_string(counter) + ".", 
                (buffer == 0 ? tags : tags2));
            else curBuffer->insert_with_tags(iter,"\t" + std::to_string(counter) + ".", (buffer == 0 ? tags : tags2));
            iter = m_refTextBuffer->end();
            curBuffer->insert(iter, "\t" + to + "\n");
        } else {
            if (brlines.find(counter) != brlines.end()) curBuffer->insert(iter, "●  "+ std::to_string(counter) + ".\t" + to + "\n");
            else curBuffer->insert(iter, "\t" + std::to_string(counter) + ".\t" + to + "\n");
        }
        iter = curBuffer->end();
    }
    lastHighlightedLine = line_actual;
    if (buffer == 0) m_TextView.set_buffer(curBuffer);
    else m_TextView2.set_buffer(curBuffer);
}

void GUIDebuggerWindow::updateCallStack(std::vector<int> ids) {
	callStackEntries->clear();
    for (unsigned int i = 0; i < ids.size(); i++) {
        Gtk::TreeModel::Row row = *(callStackEntries->append()); 
        row[callStackDispColumns.functionCallID] = ids[i];
        row[callStackDispColumns.functionCallIndex] = i;
    }      
}

int GUIDebuggerWindow::getCallIndex(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* c) {   
    Gtk::TreeModel::iterator i = callStackEntries->get_iter(path);
    Gtk::TreeModel::Row row = *i;
    return row[callStackDispColumns.functionCallIndex];
}
