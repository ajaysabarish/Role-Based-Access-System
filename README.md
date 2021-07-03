# Role-Based-Access-System

## Steps to start program
1) Pull main.cpp file to your workspace
2) Execute `g++ main.cpp`
3) Execute `.\main`


## Assumptions

1) User can have multiple roles associated, and each role will have access permission to a set of resources
2) `userId` uniquely detemrines a User
3) `resourceId` uniquely determines a Resource
4) `roleId` uniquely determines a Role
5) set of access permissions -> `[READ,WRITE,DELETE]`
6) CLI is enabled to accept permissions only in Unix permission format for `[READ,WRITE,DELETE]` ,i.e if you want a role to have `[READ,WRITE]` access to a resource, you should enter `3`.

                    READ WRITE DELETE
         Enabled:     1    2     4

         Disabled:    0    0     0

If you want to give `[READ,WRITE]` access only -> 1 + 2 + 0 => 3

If you want to give `[READ]` access only -> 1 + 0 + 0 => 1

If you want to give `[WRITE]` access only -> 0 + 2 + 0 => 2

If you want to give `[DELETE]` access only -> 0 + 0 + 4 => 4

If you want to give `[READ,WRITE,DELETE]` access only -> 1 + 2 + 4 => 7

If you want to give `[READ,DELETE]` access onyl -> 1 + 0 + 4 => 5

If you want to give `[READ,WRITE]` access only -> 1 + 2 => 3

If you don't want to give any access `[]` -> 0 + 0 + 0 => 0

For more info on this format refer [chmod](https://en.wikipedia.org/wiki/Chmod)

## Init System

System is initialized with 

Resource : resource1

Role : role1 which has `[READ,WRITE,DELETE]` access to resource resource1

User : admin who has been assigned role role1
Hence admin user has [READ,WRITE,DELETE] access to resource resource1.

## Sample Command Line interaction


```
Resource with resourceId resource1 created
Role with roleId role1 created
User with userId admin created
Added READ permission to role role1 for resource resource1  
Added WRITE permission to role role1 for resource resource1 
Added DELETE permission to role role1 for resource resource1
Added role role1 to user admin
1 -> Create new Resource 
2 -> Create new Role 
3 -> Create new User 
4 -> Add permission to existing role 
5 -> Assign existing role to existing User 
6 -> Check Access to a User for a resource 
1  
Enter resource Id
resource2
Resource with resourceId resource2 created
1 -> Create new Resource 
2 -> Create new Role 
3 -> Create new User
4 -> Add permission to existing role
5 -> Assign existing role to existing User
6 -> Check Access to a User for a resource
2
Enter role Id
role2
Role with roleId role2 created
1 -> Create new Resource
2 -> Create new Role
3 -> Create new User
4 -> Add permission to existing role
5 -> Assign existing role to existing User
6 -> Check Access to a User for a resource
3
Enter user Id
user1
User with userId user1 created
1 -> Create new Resource
2 -> Create new Role
3 -> Create new User
4 -> Add permission to existing role
5 -> Assign existing role to existing User
6 -> Check Access to a User for a resource
4
Enter roleId
role2
Enter Resource Id
resource2
Enter permissions for READ,WRITE,DELETE in Unix permissions format
1
Added READ permission to role role2 for resource resource2
1 -> Create new Resource
2 -> Create new Role
3 -> Create new User
4 -> Add permission to existing role
5 -> Assign existing role to existing User
6 -> Check Access to a User for a resource
5
 Enter roleId 
role2
 Enter UserId 
user1
Added role role2 to user user1
1 -> Create new Resource
2 -> Create new Role
3 -> Create new User
4 -> Add permission to existing role
5 -> Assign existing role to existing User
6 -> Check Access to a User for a resource
6
 Enter userId 
user1
 Enter accessType 
WRITE
 Enter resourceId 
resource2
User user1 does NOT have WRITE access for resource resource2
1 -> Create new Resource
2 -> Create new Role
3 -> Create new User
4 -> Add permission to existing role
5 -> Assign existing role to existing User
6 -> Check Access to a User for a resource
6
 Enter userId
user1
 Enter accessType
READ
 Enter resourceId
resource2
User user1 HAS READ access for resource resource2
```


  
