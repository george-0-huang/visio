# Dynamic Rule-based Pricing System

    Develop a solution that allows the business to dynamically generating product pricing from a set of rules defined 
    by the finance team. The finance team has given you an initial set of rules on how to price the products, 
    however, these rules could change at any time so we need to be able to update the rules easily and rerun the 
    product pricing to see the new prices of the products

## Getting Started

    This project provide the source code to produce a software : product.exe , which enable finance team to define 
    or update a JSON based rule to drive the software to generate the rule-based price. 

    The instructions below will cover the steps to build the project on windows 10 system to produce the binary 
    executable, along with its unit test binary excitable.
    
    Similar steps should also work for Linux with gcc (not verified) 

	
### Prerequisites


--- Install Visualstudio 2019

    Download from
        "https://visualstudio.microsoft.com/downloads"       
    Then install it on windows machine
    
--- Install GIT

    Download from
        "https://git-scm.com/downloads"
    Then install it on the windows machine

--- Install CMAKE

    Download from
        "https://cmake.org/download"
    Then install it on the windows machine
	
--- Install BOOST

    Download from
        "https://www.boost.org/users/download"
    Then  copy the unziped files to the windows machine in a folder
	       For example: C:\boost_1_72_0
	  set enviromnet variable BOOST_ROOT_1_72_0 = C:\boost_1_72_0
	

 
### Building


--- Get source code from Git

    Open "Developer Command Prompt for VS2019" , in the command windows, goto a repo foler, clone the source
        For example :
        enter: cd c:\repos
        enter: git clone https://github.com/george-0-huang/visio 
        
    Then you should have something like this to start with:
        c:\repo\visio   
        --- project                  //project dir,  common source files, include root CMakeLists
        -------person                //source files for person
        -------product               //source files for product, include sub CMakeLists to produce product.exe
        -----------rule_samples      //sample rule JSON files, used for unit test as well
        -------rule                  //source files for rule engine
        -------test                  //source files for unit , include sub CMakeLists to produce uint test's test.exe
    And there are files under each relevant directory.          

--- Initialize cmake build once

    Open "Developer Command Prompt for VS2019", in the command windows:
    enter:  cd c:\repo\visio 
    enter:  mkdir build
    enter:  cd build 
    enter:  cmake ..\proejct -DBOOST_ROOT=%BOOST_ROOT_1_72_0%

    Note: The project will automatically pull googletest dependency code from github, internet connection to github 
    is a prerequisite.
   
--- build the project:
    
    enter:  cmake --build .

    The output binaries can be located at following locations
        c:\repo\visio\build\product\debug\product.exe. 
        c:\repo\visio\build\test\debug\test.exe. 

## Continuous Integration and Manual Testing 

--- Manual Testing:

    Copy c:\repo\visio\project\product\run_sample folder to c:\repo\visio\build\test\debug\
    
    Expect to have these files under c:\repo\visio\build\test\debug
        test.exe
        rule_sample\rule_score.txt
        rule_sample\rule_state.txt
        rule_sample\rule_product_name.txt

    Then open a cmd windows:
        enter: cd c:\repo\visio\build\test]debug
        enter: test 
    The test will execuate all 24 unit tests.
    
--- Conitnuous Integration 

    The above tests are automatically triggered by gitHuab Action workflow on every push or pull request
    For example, this link to workflow records in master branch
        https://github.com/george-0-huang/visio/actions?query=branch%3Amaster

     Master pull reqeust reviewer will only accepted pull request megrer for pending changes from other branch 
     only with success workflow status.  

## Release and Deployment

--- Release 

   From command window, create a release tag and push it to the server,  
        git tag -a v1.0.0 -m "Release v1.0.0"
        git push origin v1.0.0

   The above event will invoke workflow to produce the releae asserts. 
   The release binary(product.exe) in .tar.xz and the matching source code can be found as assets from each release under
       https://github.com/george-0-huang/visio/releases
   
--- Delopyment

   product.exe  can be deployed as a standalone exe to any location on a windows system

   The command to run is : product [ProductName] [Score] [State] [RuleFileName]

   For example, (if you chose to leave product.exe at build export dir)
   
   
   enter: cd c:\repo\visio\build\product\debug
   
   enter: prodcut "7-1 ARM" 720 texas "c:\repo\visio\prodcut\build\debug\rule_sample\rule_score.txt" 
   
   it will generate following result:
   
   
         Build Product 7-1 ARM for the person (Socre : 720, state : texas )
         product.interest_rate == 4.7 (5-0.3)
         product.disqualified == false

    Note: Since rules_score.txt does not include rule on product name, 
          the product's name "7-1 ARM" has no impact on the rate

## Contributing

## Versioning

## Authors

* **George Huang** -


## License


## Acknowledgments

* Thanks for this intriguing assignment from VISIO
