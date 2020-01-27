# Dynamic Rule-based Pricing System

    Develop a solution that allows the business to dynamically generating product pricing from a set rules defined by the finance team. The finance team has given you an initial set of rules on how to price the products, however, these rules could change at any time so we need to be able to update the rules easily and rerun the product pricing to see the new prices of the products

## Getting Started

    These instructions below will  cover the stpes to build the project on windows 10 system
	
### Prerequisites


--- Install Visualstudio 2019
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
	

 
### Building

--- login to you github account
    This steps is needed for unit test, since the CMake will need to fetch googletest dependency from git

--- git clone https://github.com/george-0-huang/visio under a repo dir
       for example 
	       c:\repo\visio 
    Then you should have something like this to start with:
      c:\repo\visio   
        --- project
        -------person
        -------product
        -------rule
        -------test   
    And there are files under each relevant directory.
    The root CMakeLists.txt is c:\repo\visio\project\CMakeLists.txt 
    Note: If you boost is not under D:\\boost_1_72_0
          Update this line 
    		  set(BOOST_ROOT "D:\\boost_1_72_0")
		  to match you boost dir path  

    Open "Developer Command Prompt for VS2019"    
    enter:  cd c:\repo\visio 


    Note: The project will automatically pull googletest dependency code from github
   
--- Create project.sln
    Open "Developer Command Prompt for VS2019"
    go to the  repo folder (created from step 1.2.1), for example c:\repo\crowdstrike.

    enter:  cd c:\repo\visio 

    Option 1: Create only the default debug build (for speedy development)
    enter:  cmake proejct

    Option 2: Create release build
    enter:  cmake --build . --target ALL_BUILD --config Release

    Note:  If you have not login to git , this step will fail
   
--- build the project:
    Under the same "Developer Command Prompt for VS2019" windows under repo folder, 
    for example c:\repo\visio 
    
    enter:  msbuild proejct.sln 

    The output exe can be located at each relavant folder
    i.e   
        c:\repo\visio\product\debug\product.exe. 
        c:\repo\visio\test\debug\test.exe. 
```


## Running the tests

    Copy c:\repo\visio\project\product\run_spec folder to c:\repo\visio\test\debug\
	Expect to have these files under c:\repo\visio\test\debug\
	     test.exe
		 rule_spec\rule_score.txt
		 rule_spec\rule_state.txt
		 rule_spec\rule_product_name.txt

    Then open a cmd windows:
	     enter: cd c:\repo\visio\test]debug
		 enter: test 
    The test will execuate all 24 unit tests 


```
Give an example
```

## Deployment

   product.exe can be deployed as astandalone exe from any location on a windows system
   For example , if you chose to eave it at is build export dir, 
   To run it under a cmd windows:
   enter:
        cd c:\repo\visio\product\debug
        product [ProductName] [Score] [State] [RuleFileName]


## Contributing
read [CONTRIBUTING.md](https://gist.github.com/PurpleBooth/b24679402957c63ec426) for details on our code of conduct, and the process for submitting pull requests to us.

## Versioning

## Authors

* **George Huang** -


## License


## Acknowledgments

* Thanks for the assignment from VISIO

