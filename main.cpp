#include<iostream>
#include<vector>
#include<map>
#include<set>
#include<string>

enum AccessTypes{READ,WRITE,DELETE};

std::map<AccessTypes,std::string>accessEnum = {
        {AccessTypes::READ,"READ"},
        {AccessTypes::WRITE,"WRITE"},
        {AccessTypes::DELETE,"DELETE"}
};

std::map<std::string,AccessTypes>accessEnumMap = {
        {"READ",AccessTypes::READ},
        {"WRITE",AccessTypes::WRITE},
        {"DELETE",AccessTypes::DELETE}
};

class Resource {
    std::string resourceId;
public:
    Resource() {};
    Resource(std::string resourceId) : resourceId(resourceId) {};
    bool operator==( Resource & rhs)
    {
        return this->getResourceId() ==rhs.getResourceId();
    }
    bool operator<(const Resource& rhs) const
    {
        return resourceId < rhs.resourceId;
    }
    std::string getResourceId();
    void setResourceId(std::string);

};

class Role {
    std::string roleId;
    std::map<Resource,std::vector<AccessTypes>>permissions;
public:
    Role() {};
    Role(std::string roleId) {
        this->roleId = roleId;
    }
    bool operator==( Role & rhs)
    {
        return this->getRoleId() ==rhs.getRoleId();
    }
    std::string getRoleId();
    void setRoleId(std::string);
    std::map<Resource,std::vector<AccessTypes>>getPermissions();
    void setPermissions(std::map<Resource,std::vector<AccessTypes>>);
    void addPermissions(Resource,AccessTypes);
    bool checkAccess(AccessTypes,Resource);
};

class User {
    std::string userId;
    std::vector<Role>roles;
public:
    User() {};

    User(std::string userId) : userId(userId) {};
    bool operator==( User & rhs)
    {
        return this->getUserId() ==rhs.getUserId();
    }
    std::string getUserId();
    void setUserId(std::string);
    void addRole(Role);
    void removeRole(std::string);
    std::vector<Role>& getRoles();
    void checkAccess(AccessTypes,Resource); // accessType,resource
};




class System {
    std::vector<User> users;
    std::vector<Role> roles;
    std::vector<Resource> resources;
public:
    System() {};
    int findUserIdx(std::string userId) {
        for(int i=0; i<users.size(); i++) {
            if(users[i].getUserId() == userId) {
                return i;
            }
        }
        std::cout<< "No user found with such User Id";
    }
    int findRoleIdx(std::string roleId) {
        for(int i=0;i<roles.size();i++) {
            if(roles[i].getRoleId() == roleId) {
                return i;
            }
        }

        std::cout<< "No role found with such Role Id";
    }

    int findResourceIdx(std::string resourceId) {
        for(int i=0;i<resources.size();i++) {
            if(resourceId == resources[i].getResourceId()) {
                return i;
            }
        }
        std::cout<< "No resource found with such resource Id";
    }

    void createResource(std::string resourceId) {
        for(auto r : resources) {
            if(r.getResourceId() == resourceId) {
                std::cout<<"Resource with resourceId "<<resourceId<<" already exists\n";
                return ;
            }
        }
        Resource resource(resourceId);

        resources.push_back(resource);
        std::cout<<"Resource with resourceId "<<resourceId<<" created\n";
    }
    void createRole(std::string roleId) {
        for(auto r : roles) {
            if(r.getRoleId() == roleId) {
                std::cout<<"Role with roleId "<<roleId<<" already exists\n";
                return ;
            }
        }
        Role role(roleId);
        roles.push_back(role);
        std::cout<<"Role with roleId "<<roleId<<" created\n";
    }
    void createUser(std::string userId) {
        for(auto u : users) {
            if(u.getUserId() == userId) {
                std::cout<<"User with userId "<<userId<<" already exists\n";
                return ;
            }
        }
        User user(userId);

        users.push_back(user);
        std::cout<<"User with userId "<<userId<<" created\n";
    }
    void addPermissionsToRole(std::string roleId,std::string resourceId,int permission) {
        Role& role = roles[findRoleIdx(roleId)];
        Resource& resource = resources[findResourceIdx(resourceId)];

        for(int i=0;i<3;i++) {
            if(permission&(1<<i)) {
                AccessTypes accessType = static_cast<AccessTypes>(i);

                role.addPermissions(resource,accessType);
                std::cout<<"Added "<<accessEnum[accessType]<<" permission to role "<<role.getRoleId()<<"for resource "<<resource.getResourceId()<<std::endl;
            }
        }
    }
    void addRoleToUser(std::string userId, std::string roleId) {
        User& user = users[findUserIdx(userId)];
        Role& role = roles[findRoleIdx(roleId)];
        user.addRole(role);
        std::cout<<"Added role "<<roleId<<" to user "<<userId<<std::endl;
    }
    
    void checkAccess(std::string userId, std::string resourceId,std::string access) {
        User& user = users[findUserIdx(userId)];
        Resource& resource = resources[findResourceIdx(resourceId)];
        user.checkAccess(accessEnumMap[access],resource);
    }

};



std::string User::getUserId() {
    return this->userId;
}

void User::setUserId(std::string userId) {
    this->userId = userId;
}

void User::addRole(Role newRole) {
    roles.push_back(newRole);
}

void User::removeRole(std::string delRoleId) {
    bool found = false;
    for(int i=0;i<roles.size();i++) {
        if(roles[i].getRoleId() == delRoleId) {
            roles.erase(roles.begin() + i);
            found = true;
            break;
        }
    }
    if(!found) {
        std::cout<<"Role "<<delRoleId<<" not found "<<std::endl;
    } else {
        std::cout<<"Role "<<delRoleId<<" successfully deleted \n";
    }
}

std::vector<Role>& User::getRoles() {
    return roles;
}

void User::checkAccess(AccessTypes accessType, Resource resource) {
    for(auto role : roles) {
        if(role.checkAccess(accessType, resource)) {
            std::cout<<"User "<<userId<<" HAS "<<accessEnum[accessType]<<" access for resource "<<
                     resource.getResourceId()<<std::endl;
            return ;
        }
    }
    std::cout<<"User "<<userId<<" does NOT have "<<accessEnum[accessType]<<" access for resource "<<
             resource.getResourceId()<<std::endl;
}

std::string Role::getRoleId() {
    return roleId;
}

void Role::setRoleId(std::string roleId){
    this->roleId = roleId;
}

void Role::setPermissions(std::map<Resource,std::vector<AccessTypes>> permissions) {
    this->permissions = permissions;
}

std::map<Resource,std::vector<AccessTypes>> Role::getPermissions() {
    return permissions;
}

std::string Resource::getResourceId() {
    return resourceId;
}

void Resource::setResourceId(std::string resourceId) {
    this->resourceId = resourceId;
}

void Role::addPermissions(Resource resource, AccessTypes accessType) {
    bool alreadyPresent = false;
    for(auto type:permissions[resource]) {
        if(type == accessType) {
            alreadyPresent = true;
        }
    }
    if(!alreadyPresent) {
        permissions[resource].push_back(accessType);
    }
}

bool Role::checkAccess(AccessTypes accessType,Resource resource) {
    std::cout<<accessType<<" "<<resource.getResourceId()<<std::endl;
    for(auto type: permissions[resource]) {
        if(type == accessType) {
            return true;
        }
    }
    return false;
}

int main() {
    /*
    Add resource [input -> resourceId]
    Add a new role [input -> roleId]
    Add a new user [userId]
    Add permissions to a role[roleId,resourceId,accessType(read,write,delete)]
    Add the role to a user[userId,roleId]
    Given User,access type, resource -> check access rights [userId,accessType,resourceId]
    */
    System system;
    system.createResource("resource1");
    system.createRole("role1");
    system.createUser("admin");
    system.addPermissionsToRole("role1","resource1",7);
    system.addRoleToUser("admin","role1");
    system.checkAccess("admin","resource1","DELETE");

    while(true) {
        std::cout<<"1 -> Create new Resource \n";
        std::cout<<"2 -> Create new Role \n";
        std::cout<<"3 -> Create new User \n";
        std::cout<<"4 -> Add permission to existing role \n";
        std::cout<<"5 -> Assign existing role to existing User \n";
        std::cout<<"6 -> Check Access to a User for a resource \n";
        int op;
        std::cin>>op;
        switch(op) {
            case 1: { // Create Resource
                std::string resourceId;
                std::cout<<"Enter resource Id"<<std::endl;
                std::cin>>resourceId;
                system.createResource(resourceId);

                break;
            }
            case 2: {
                // Create Role
                std::string roleId;
                std::cout<<"Enter role Id"<<std::endl;
                std::cin>>roleId;
                system.createRole(roleId);
                break;
            }
            case 3: {
                //Create User
                std::string userId;
                std::cout<<"Enter user Id"<<std::endl;
                std::cin>>userId;
                system.createUser(userId);
                break;
            }
            case 4: {
                // Add permission to role
                std::string roleId,resourceId;
                std::cout<<"Enter roleId\n";
                std::cin>>roleId;
                std::cout<<"Enter Resource Id\n";
                std::cin>>resourceId;
                std::cout<<"Enter permissions for READ,WRITE,DELETE in Unix permissions format\n";
                int permission;
                std::cin>>permission;
                system.addPermissionsToRole(roleId,resourceId,permission);

                break;
            }
            case 5: {
                // Add role to User
                std::string roleId,userId;
                std::cout<<" Enter roleId \n";
                std::cin>>roleId;
                std::cout<<" Enter UserId \n";
                std::cin>>userId;
                system.addRoleToUser(userId,roleId);
                break;
            }
            case 6: {
                // check Access
                std::string userId,accessType,resourceId;
                std::cout<<" Enter userId \n";
                std::cin>>userId;
                std::cout<<" Enter accessType \n";
                std::cin>>accessType;
                std::cout<<" Enter resourceId \n";
                std::cin>>resourceId;
                system.checkAccess(userId,resourceId,accessType);
                break;
            }
            default : {
                std::cout<<"Invalid option\n";break;
            }

        }
    }


}
