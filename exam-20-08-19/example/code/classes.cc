

class parent{
public:
    parent(int i) : i{i}{

    }
private:    
    int i;
};

int main(){
    parent a {6};
    parent b = a;
}