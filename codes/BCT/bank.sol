//SPDX-License-Identifier: unlisend
pragma solidity ^0.8.4;

contract Bank{
    address public accHolder;
    uint256 balance = 0;

    constructor(){
        accHolder = msg.sender;
    }


    function withdraw() payable public{
        require(msg.sender == accHolder, "You are not the accHolder.");
        require(balance > 0, "No money to withdraw");
        payable(msg.sender).transfer(balance);
        balance = 0;
    }
    function deposit() payable public {
        require(msg.sender == accHolder, "You are not the accHolder.");
        require(msg.value > 0, "No money to deposit");
        balance += msg.value;
    }

    function showBalance() public view returns(uint256){
        require(msg.sender == accHolder, "You are not the accHolder.");
        return balance;
    }
}