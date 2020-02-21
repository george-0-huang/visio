# Dynamic Rule-based Pricing System

    Develop a solution that allows the business to dynamically generating product pricing from a set rules defined 
    by the finance team. The finance team has given you an initial set of rules on how to price the products, 
    however, these rules could change at any time so we need to be able to update the rules easily and rerun the 
    product pricing to see the new prices of the products

## Getting Started

    This project provide the source code to produce a software : produce.exe , which enable finance team to define 
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
	  For example: D:\boost_1_72_0
	

 
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

    Note: If BOOST is not installed under D:\\boost_1_72_0
          To match your BOOST path, update this line in c:\repo\visio\project\CMakeLists.txt 
    		      set(BOOST_ROOT "D:\\boost_1_72_0")
            

--- Create project.sln

    Open "Developer Command Prompt for VS2019", in the command windows:
    enter:  cd c:\repo\visio 

    Option 1: Create only the default debug build (for speedy development)
    enter:  cmake proejct

    Option 2: Create release build
    enter:  cmake --build . --target ALL_BUILD --config Release

    Note: The project will automatically pull googletest dependency code from github, internet connection to github 
    is a prerequisite.
   
--- build the project:

    Under the same "Developer Command Prompt for VS2019" windows under repo folder, 
    for example c:\repo\visio 
    
    enter:  msbuild proejct.sln 

    The output binaries can be located at following locations
        c:\repo\visio\product\debug\product.exe. 
        c:\repo\visio\test\debug\test.exe. 

## Running the tests

    Copy c:\repo\visio\project\product\run_sample folder to c:\repo\visio\test\debug\
    
    Expect to have these files under c:\repo\visio\test\debug
        test.exe
        rule_sample\rule_score.txt
        rule_sample\rule_state.txt
        rule_sample\rule_product_name.txt

    Then open a cmd windows:
        enter: cd c:\repo\visio\test]debug
        enter: test 
    The test will execuate all 24 unit tests.


## Deployment

   product.exe can be deployed as a standalone exe to any location on a windows system

   The command to run is : product [ProductName] [Score] [State] [RuleFileName]

   For example, (if you chose to leave product.exe at build export dir)
   
   
   enter: cd c:\repo\visio\product\debug
   
   enter: prodcut "7-1 ARM" 720 texas "c:\repo\visio\prodcut\debug\rule_sample\rule_score.txt" 
   
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
