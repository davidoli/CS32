void listAll(const MenuItem* m, string path) // two-parameter overload
{
    if(path != "")
        cout << path << endl;
    
    if(m->menuItems() != NULL && !m->menuItems()->empty()){
        for(int i = 0; i < m->menuItems()->size();i++){
            MenuItem* menu = m->menuItems()->at(i);
            if(path == "")
                listAll(menu, menu->name());
            else
                listAll(menu, path + "/" + menu->name());
        }
    }
    
}
