#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>

int lenght = 0;

template <typename T>
std::ostream& operator<<(std::ostream& output, const std::vector<T>& v)
{
    output << "[ ";
    std::copy(v.begin(), v.end(), std::ostream_iterator<T>(output, ", "));   
    output << " ]";
    return output;
}

std::vector<std::string> all_posible_comb(std::string all_inputs){
    std::vector<std::string> out;
    do{
        std::string work = all_inputs.substr(0,lenght);
        do{
            if(!std::count(out.begin(),out.end(),work)){
                out.push_back(work);
            }
        }while(std::next_permutation(work.begin(),work.end()));
    }while(std::next_permutation(all_inputs.begin(),all_inputs.end()));
    return out;
}
bool check_pos(std::string item,std::string rule,bool is_right){
    bool rm = !is_right;
    for(int i=0;i<lenght;i++){
        if(is_right) rm = rm || rule[i]==item[i];
        else if (rule[i]==item[i]) return false;
    }
    return rm;
}
bool check_count(std::string item,std::string rule,int count,bool Pos=false){
    int j=0;
    for(int i=0;i<lenght;i++){
        if(Pos){
            if(rule[i]==item[i]) j++;
        }else{
            for(int k=0;k<lenght;k++){
                if(rule[k]==item[i]) {
                    j++;
                    break;
                }
            }
        }
    }
    return j==count;
}
int check_and_exit(std::vector<std::string> prop,std::string where){
    if(prop.size() == 1){
        std::cout<<"Result: "<<prop.at(0)<<std::endl;
        return 0;
    }else if(prop.size() == 0){
        std::cout<<"Something wrong: "<<where<<std::endl;
        return 1;
    }
    return -1;
}

int main(){
    std::cout<<"Key lenght: ";
    std::cin>>lenght;
    std::string nrgh, orpr, orwp1, orwp2, trwp;
    //nrgh
    std::cout<<"Code with no right: ";
    std::cin>>nrgh;
    if(nrgh.size()!=lenght){
        std::cout<<"Wrong key length"<<std::endl;
        return 1;
    }else {
        //Check if only numbers and unique
        for(std::string::iterator sym = nrgh.begin();sym!=nrgh.end();sym++){
            if(*sym<'0'||*sym>'9'){
                std::cout<<"Wrong key: key can be only with numbers"<<std::endl;
                return 1;
            }
            if(std::count(nrgh.begin(),nrgh.end(),*sym)>=2){
                std::cout<<"Wrong key: key numbers must be unique"<<std::endl;
                return 1;
            }
        }
    }
    //orpr
    std::cout<<"Code with "<<lenght-2<<" right number and right pos: ";
    std::cin>>orpr;
    if(orpr.size()!=lenght){
        std::cout<<"Wrong key length"<<std::endl;
        return 1;
    }else {
        //Check if only numbers and unique
        for(std::string::iterator sym = orpr.begin();sym!=orpr.end();sym++){
            if(*sym<'0'||*sym>'9'){
                std::cout<<"Wrong key: key can be only with numbers"<<std::endl;
                return 1;
            }
            if(std::count(orpr.begin(),orpr.end(),*sym)>=2){
                std::cout<<"Wrong key: key numbers must be unique"<<std::endl;
                return 1;
            }
        }
    }
    // orwp1
    std::cout<<"Code with "<<lenght-2<<" right number and wrong pos: ";
    std::cin>>orwp1;
    if(orwp1.size()!=lenght){
        std::cout<<"Wrong key length"<<std::endl;
        return 1;
    }else {
        //Check if only numbers and unique
        for(std::string::iterator sym = orwp1.begin();sym!=orwp1.end();sym++){
            if(*sym<'0'||*sym>'9'){
                std::cout<<"Wrong key: key can be only with numbers"<<std::endl;
                return 1;
            }
            if(std::count(orwp1.begin(),orwp1.end(),*sym)>=2){
                std::cout<<"Wrong key: key numbers must be unique"<<std::endl;
                return 1;
            }
        }
    }
    // orwp2
    std::cout<<"Second code with "<<lenght-2<<" right number and wrong pos: ";
    std::cin>>orwp2;
    if(orwp2.size()!=lenght){
        std::cout<<"Wrong key length"<<std::endl;
        return 1;
    }else {
        //Check if only numbers and unique
        for(std::string::iterator sym = orwp2.begin();sym!=orwp2.end();sym++){
            if(*sym<'0'||*sym>'9'){
                std::cout<<"Wrong key: key can be only with numbers"<<std::endl;
                return 1;
            }
            if(std::count(orwp2.begin(),orwp2.end(),*sym)>=2){
                std::cout<<"Wrong key: key numbers must be unique"<<std::endl;
                return 1;
            }
        }
    }
    // trwp
    std::cout<<"Code with "<<lenght-1<<" right number and wrong pos: ";
    std::cin>>trwp;
    if(trwp.size()!=lenght){
        std::cout<<"Wrong key length"<<std::endl;
        return 1;
    }else {
        //Check if only numbers and unique
        for(std::string::iterator sym = trwp.begin();sym!=trwp.end();sym++){
            if(*sym<'0'||*sym>'9'){
                std::cout<<"Wrong key: key can be only with numbers"<<std::endl;
                return 1;
            }
            if(std::count(trwp.begin(),trwp.end(),*sym)>=2){
                std::cout<<"Wrong key: key numbers must be unique"<<std::endl;
                return 1;
            }
        }
    }
    std::string rep_sym = "*";
    //Remove non right
    for(int i=0;i<lenght;i++){
        for(int j=0;j<lenght;j++){
            if(orpr.at(j)==nrgh.at(i)){
                orpr.replace(j,1,rep_sym);
            }
            if(orwp1.at(j)==nrgh.at(i)){
                orwp1.replace(j,1,rep_sym);
            }
            if(orwp2.at(j)==nrgh.at(i)){
                orwp2.replace(j,1,rep_sym);
            }
            if(trwp.at(j)==nrgh.at(i)){
                trwp.replace(j,1,rep_sym);
            }
        }   
    }
    // Recheck rules (Later)

    // Remove at same pos as orpr

    for(int i=0;i<lenght;i++){
        if(orwp1.at(i)==orpr.at(i)||orwp2.at(i)==orpr.at(i)||trwp.at(i)==orpr.at(i)){
            if(orwp1.find(orpr.at(i))!=std::string::npos) orwp1.replace(orwp1.find(orpr.at(i)),1,rep_sym);
            if(orwp2.find(orpr.at(i))!=std::string::npos) orwp2.replace(orwp2.find(orpr.at(i)),1,rep_sym);
            if(trwp.find(orpr.at(i))!=std::string::npos) trwp.replace(trwp.find(orpr.at(i)),1,rep_sym);
            orpr.replace(i,1,rep_sym);
        }
    }

    std::string left = "";
    for(int i=0;i<lenght;i++){
        if(orpr.at(i)!=rep_sym.at(0)&&!std::count(left.begin(),left.end(),orpr.at(i))) left+=orpr.at(i);
        if(orwp1.at(i)!=rep_sym.at(0)&&!std::count(left.begin(),left.end(),orwp1.at(i))) left+=orwp1.at(i);
        if(orwp2.at(i)!=rep_sym.at(0)&&!std::count(left.begin(),left.end(),orwp2.at(i))) left+=orwp2.at(i);
        if(trwp.at(i)!=rep_sym.at(0)&&!std::count(left.begin(),left.end(),trwp.at(i))) left+=trwp.at(i);
    }
    std::sort(left.begin(),left.end());

    std::vector<std::string> all_pos = all_posible_comb(left);
    std::vector<std::string> all_pos_temp;
    int ext = -1;
    
    std::copy_if(all_pos.begin(),all_pos.end(),std::back_inserter(all_pos_temp), [&](std::string s){return check_pos(s,orpr,true);});
    all_pos.clear();
    all_pos.assign(all_pos_temp.begin(),all_pos_temp.end());
    all_pos_temp.clear();
    if((ext=check_and_exit(all_pos,"orpr"))>-1) return ext;
    
    std::copy_if(all_pos.begin(),all_pos.end(),std::back_inserter(all_pos_temp), [&](std::string s){return check_count(s,trwp,lenght-1);});
    all_pos.clear();
    all_pos.assign(all_pos_temp.begin(),all_pos_temp.end());
    all_pos_temp.clear();
    if((ext=check_and_exit(all_pos,"trwp(2)"))>-1) return ext;
    
    std::copy_if(all_pos.begin(),all_pos.end(),std::back_inserter(all_pos_temp), [&](std::string s){return check_count(s,orwp1,lenght-2);});
    all_pos.clear();
    all_pos.assign(all_pos_temp.begin(),all_pos_temp.end());
    all_pos_temp.clear();
    if((ext=check_and_exit(all_pos,"orwp1(2)"))>-1) return ext;
    
    std::copy_if(all_pos.begin(),all_pos.end(),std::back_inserter(all_pos_temp), [&](std::string s){return check_count(s,orwp2,lenght-2);});
    all_pos.clear();
    all_pos.assign(all_pos_temp.begin(),all_pos_temp.end());
    all_pos_temp.clear();
    if((ext=check_and_exit(all_pos,"orwp2(2)"))>-1) return ext;
    
    std::copy_if(all_pos.begin(),all_pos.end(),std::back_inserter(all_pos_temp), [&](std::string s){return check_count(s,orpr,lenght-2,true);});
    all_pos.clear();
    all_pos.assign(all_pos_temp.begin(),all_pos_temp.end());
    all_pos_temp.clear();
    if((ext=check_and_exit(all_pos,"orpr(2)"))>-1) return ext;

    std::copy_if(all_pos.begin(),all_pos.end(),std::back_inserter(all_pos_temp), [&](std::string s){return check_pos(s,trwp,false);});
    all_pos.clear();
    all_pos.assign(all_pos_temp.begin(),all_pos_temp.end());
    all_pos_temp.clear();
    if((ext=check_and_exit(all_pos,"trwp"))>-1) return ext;

    std::copy_if(all_pos.begin(),all_pos.end(),std::back_inserter(all_pos_temp), [&](std::string s){return check_pos(s,orwp1,false);});
    all_pos.clear();
    all_pos.assign(all_pos_temp.begin(),all_pos_temp.end());
    all_pos_temp.clear();
    if((ext=check_and_exit(all_pos,"orwp1"))>-1) return ext;

    std::copy_if(all_pos.begin(),all_pos.end(),std::back_inserter(all_pos_temp), [&](std::string s){return check_pos(s,orwp2,false);});
    all_pos.clear();
    all_pos.assign(all_pos_temp.begin(),all_pos_temp.end());
    all_pos_temp.clear();
    if((ext=check_and_exit(all_pos,"orwp2"))>-1) return ext;
    
    //Output if something left
    
    std::cout<<all_pos.size()<<" "<<all_pos;

    
}
