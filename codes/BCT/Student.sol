//SPDX-License-Identifier: unlisend
pragma solidity ^0.8.4;

contract StudentData{

    struct Student{
        string name;
        uint rollno;
    }

    Student[] public studentarr;

    function addStudent(string memory name, uint rollno) public {
        for(uint i=0;i<studentarr.length;i++){
            if(studentarr[i].rollno == rollno){
                revert("Student with this roll no already exist");
            }
        }
        studentarr.push(Student(name,rollno));
    }

    function getStudentsLength() public view returns (uint){
        return studentarr.length;
    }

    function displayAllStudents() public view returns (Student[] memory){
        return studentarr;
    }

    function getStudentByIndex(uint idx) public view returns(Student memory){
        require(idx < studentarr.length, "index out of bound");
        return studentarr[idx];
    }

    //fallback

    fallback() external payable {
        //handle external function which are not present in this contract
     }

     receive() external payable {
        //handle ether send by other user without mention the data
      }
}