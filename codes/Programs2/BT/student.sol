// SPDX-License-Identifier: MIT
pragma solidity >=0.7.0 <0.9.0;

contract StudentManagement {
    
    struct Student {
        uint id;
        string name;
        string department;
        bool exists;
    }
    
    // Array to store students
    Student[] public students;
    
    // Event to log student addition
    event StudentAdded(uint id, string name);
    
    // Add a new student
    function addStudent(uint _id, string memory _name, string memory _dept) public {
        students.push(Student(_id, _name, _dept, true));
        emit StudentAdded(_id, _name);
    }
    
    // Get student details by ID
    function getStudent(uint _id) public view returns (string memory, string memory) {
        for(uint i = 0; i < students.length; i++) {
            if(students[i].id == _id) {
                return (students[i].name, students[i].department);
            }
        }
        return ("Not Found", "Not Found");
    }
    
    // Get total number of students
    function getTotalStudents() public view returns (uint) {
        return students.length;
    }
    
    fallback() external payable {
        revert("Function not found");
    }
    
    receive() external payable {
        revert("Cannot accept ETH");
    }
}