#ifndef GUI_DEBUGGER_WINDOW_H
#define GUI_DEBUGGER_WINDOW_H

#include <gtkmm/applicationwindow.h>
#include <gtkmm/button.h>
#include <gtkmm/box.h>
#include <gtkmm/treeview.h>
#include <gtkmm/treestore.h>
#include <gtkmm/liststore.h>
#include <gtkmm/grid.h>
#include <gtkmm/scrolledwindow.h>
#include <glibmm/refptr.h>
#include <gtkmm/frame.h>
#include <gtkmm/textview.h>
#include <gtkmm/enums.h>
#include <stack>
#include <set>

class GUIDebuggerWindow : public Gtk::ApplicationWindow {
public:
    GUIDebuggerWindow(); 
    virtual ~GUIDebuggerWindow(){};
    Gtk::Button continueButton, stepOverButton, stepInButton, pauseButton;
    Gtk::Button addBreakPointButton, removeBreakPointButton, clearAllBreakpointsButton;
    Glib::RefPtr<Gtk::TreeSelection> selection;
    Gtk::TreeView callStackView; 
   
    void addVariableRow(std::string name, std::string value);
    void addVariableChildRow(std::string name, std::string value);
    void popOut();
    void clearVariables();
    int getBreakPointValueFromEntry();
    void updateCallStack(std::vector<int> ids);
    int getCallIndex(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* c);

    void fillBuffer(std::string code, int buffer);
    void updateBuffer(int line, int buffer);
    std::set<int> brlines;
    int lastHighlightedLine;
   
protected:
    Gtk::Grid masterGrid;
    Gtk::Box buttonBox;
    Gtk::Box breakPointBox;
    Gtk::Box innerBreakPointEntryBox;
    Gtk::Box innerBreakPointButtonsBox;
    Gtk::Entry breakPointEntry;      

    class VariablesDisplayColumns : public Gtk::TreeModel::ColumnRecord{
    public:
        VariablesDisplayColumns(){
            this->add(variableNameColumn);
            this->add(variableValueColumn);
        }

        Gtk::TreeModelColumn<Glib::ustring> variableNameColumn;
        Gtk::TreeModelColumn<Glib::ustring> variableValueColumn;
    };

    class CallStackColumns : public Gtk::TreeModel::ColumnRecord {
    public:
        CallStackColumns() {
            this->add(functionCallID);
            this->add(functionCallIndex);
        }
        Gtk::TreeModelColumn<int> functionCallID;
        Gtk::TreeModelColumn<int> functionCallIndex;
    };

    VariablesDisplayColumns varDispColumnns;
    CallStackColumns callStackDispColumns;
    Gtk::ScrolledWindow variablesContainer;
    Glib::RefPtr<Gtk::TreeStore> variablesDisplayEntries;
    Gtk::TreeView variablesDisplay;     
    Glib::RefPtr<Gtk::ListStore> callStackEntries;
    Gtk::ScrolledWindow callStackContainer;
    Gtk::Grid codeGrid;
    Gtk::Frame codeContainerFrame;
    Gtk::Frame codeContainerFrame2;

    std::vector<Glib::RefPtr<Gtk::TextTag>> tags, tags2;
    Glib::RefPtr<Gtk::TextBuffer> m_refTextBuffer;
    Glib::RefPtr<Gtk::TextBuffer> m_refTextBuffer2;
    Gtk::ScrolledWindow m_ScrolledWindow;
    Gtk::ScrolledWindow m_ScrolledWindow2;
    Gtk::TextView m_TextView;
    Gtk::TextView m_TextView2;
private:
    Gtk::TreeModel::Row lastRowInserted;    
    std::stack<Gtk::TreeModel::Row> st;
    std::string src1;
    std::string src2;
};

#endif