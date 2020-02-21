# Dynamic Rule-based Pricing System

<<<<<<< HEAD
    Develop a solution that allows the business to dynamically generating product pricing from a set rules defined by the finance team. The finance team has given you an initial set of rules on how to price the products, however, these rules could change at any time so we need to be able to update the rules easily and rerun the product pricing to see the new prices of the products

## Getting Started

    This project provide the source code to produce a software : produce.exe , which enable finance team to define/update a JSON based rule to drive the softeware to generate the rule based price. 

    These instructions below will cover the stpes to build the project on windows 10 system (smilars steps shold also works for Linux with gcc, not verified)
=======
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
>>>>>>> master

	
### Prerequisites


--- Install Visualstudio 2019
<<<<<<< HEAD
    Download from
        https://visualstudio.microsoft.com/downloads/
    Then install it on windows machine
--- Install GIT
    Download from
        https://git-scm.com/downloads
    Then install it on the windows machine

    Optional: GitHub Deskop
    Download from 
        https://desktop.github.com/

--- Install CMAKE
    Download from
        https://cmake.org/download/
    Then install it on the windows machine
	
--- Install BOOST
    Download from
        https://www.boost.org/users/download/
    Then  copy the unziped files the windows machine 
	    For example: D:\boost_1_72_0
=======

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
>>>>>>> master
	

 
### Building


<<<<<<< HEAD
--- git clone https://github.com/george-0-huang/visio under a repo dir
       for example 
	       c:\repo\visio 
    Then you should have something like this to start with:
      c:\repo\visio   
        --- project                  //project dir,  common source files, include root CMakeLists
        -------person                //source files for person
        -------product               //source files for product, include sub CMakeLists to produce product.exe
		-----------rule_samples      //sample rule JSON files, used for unit test as well
=======
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
>>>>>>> master
        -------rule                  //source files for rule engine
        -------test                  //source files for unit , include sub CMakeLists to produce uint test's test.exe
    And there are files under each relevant directory.

<<<<<<< HEAD
    Note: If you boost is not under D:\\boost_1_72_0
          Update this line 
    		  set(BOOST_ROOT "D:\\boost_1_72_0")
		  to match you boost dir path  


--- Create project.sln
    Open "Developer Command Prompt for VS2019"
    go to the  repo folder (created from step 1.2.1), for example c:\repo\crowdstrike.

=======
    Note: If BOOST is not installed under D:\\boost_1_72_0
          To match your BOOST path, update this line in c:\repo\visio\project\CMakeLists.txt 
    		      set(BOOST_ROOT "D:\\boost_1_72_0")
            

--- Create project.sln

    Open "Developer Command Prompt for VS2019", in the command windows:
>>>>>>> master
    enter:  cd c:\repo\visio 

    Option 1: Create only the default debug build (for speedy development)
    enter:  cmake proejct

    Option 2: Create release build
    enter:  cmake --build . --target ALL_BUILD --config Release

<<<<<<< HEAD
    Note: The project will automatically pull googletest dependency code from github, internet connection to github is a Prerequisite
   
--- build the project:
=======
    Note: The project will automatically pull googletest dependency code from github, internet connection to github 
    is a prerequisite.
   
--- build the project:

>>>>>>> master
    Under the same "Developer Command Prompt for VS2019" windows under repo folder, 
    for example c:\repo\visio 
    
    enter:  msbuild proejct.sln 

<<<<<<< HEAD
    The output exe can be located at each relavant folder
    i.e   
        c:\repo\visio\product\debug\product.exe. 
        c:\repo\visio\test\debug\test.exe. 
```

=======
    The output binaries can be located at following locations
        c:\repo\visio\product\debug\product.exe. 
        c:\repo\visio\test\debug\test.exe. 
>>>>>>> master

## Running the tests

    Copy c:\repo\visio\project\product\run_sample folder to c:\repo\visio\test\debug\
<<<<<<< HEAD
	Expect to have these files under c:\repo\visio\test\debug\
	     test.exe
		 rule_sample\rule_score.txt
		 rule_sample\rule_state.txt
		 rule_sample\rule_product_name.txt

    Then open a cmd windows:
	     enter: cd c:\repo\visio\test]debug
		 enter: test 
    The test will execuate all 24 unit tests 
=======
    
    Expect to have these files under c:\repo\visio\test\debug
        test.exe
        rule_sample\rule_score.txt
        rule_sample\rule_state.txt
        rule_sample\rule_product_name.txt

    Then open a cmd windows:
        enter: cd c:\repo\visio\test]debug
        enter: test 
    The test will execuate all 24 unit tests.
>>>>>>> master


## Deployment

<<<<<<< HEAD
   product.exe can be deployed as astandalone exe from any location on a windows system
   For example , if you chose to eave it at is build export dir, 
   To run it under a cmd windows:
   enter:
        cd c:\repo\visio\product\debug
        product [ProductName] [Score] [State] [RuleFileName]
		
		For example 
		   prodcut "7-1 ARM" 720 texas "c:\repo\visio\prodcut\debug\rule_sample\rule_score.txt"
		   
           it will generate following result:
               Build Product 7-1 ARM for the person (Socre : 720, state : texas )
               product.interest_rate == 4.7 (5-0.3)
               product.disqualified == false


## Contributing
read [CONTRIBUTING.md](https://gist.github.com/PurpleBooth/b24679402957c63ec426) for details on our code of conduct, and the process for submitting pull requests to us.
=======
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
>>>>>>> master

## Versioning

## Authors

* **George Huang** -


## License


## Acknowledgments

* Thanks for this intriguing assignment from VISIO
<<<<<<< HEAD

=======
>>>>>>> master
