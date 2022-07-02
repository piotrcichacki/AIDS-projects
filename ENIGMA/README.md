# EnigmaNumbers

Algorithms and Data Structures project

### Instructions

Your task is to implement a variant of an Enigma machine which encrypts messages in an alphabet consisting of n letters denoted by numbers {1,2,...,n}. Symbol 0 ends the message. <br/>
Rotors Wx={wx0, wx1,...,wxn}and reflectors Ry={ry0, ry1,...,ryn} are given as permutations of numbers {1,2,...,n} and simulate mechanical parts that can be used by an operator. The internal "wiring" of these parts does not change. <br/>
Typing a letter into the input encrypts it by passing it through the rotors into reflector and back through the rotors in the inverse sequence. A stationary sequence of rotors and a reflector represent a simple substitution cipher, it is their movement which makes the decoding chalenging.<br/>
Each rotor can move counterclockwise by at most one step during each encoding. The first rotor moves before every encoding; therefore if the initial position of this single rotor is denoted by the last letter of the alphabet (i.e. n, see example I) the first letter is encoded according to substitutions as stated in the rotor's definition.<br/>
In case there are more than 3 rotors only the first 3 rotate.<br/>
Input can be thought as divided into two parts: definitions of pieces of the machine and p instructions how to encode a given message using some of those parts. Before encoding a message the machine is assembled from k out of m rotors and a single reflector (out of l) and the rotors are set to some initial positions. Refer to the input section for details.<br/>

### Input
Defintions of parts of the machine:
<ul>
    <li>n- number of letters (numbers) in the alphabet</li>
    <li>m - number of rotors, followed by their definitions W0,...,Wm-1 (definition of rotor Wi - permutation of the alphabet; number of letters which cause turnover, followed by these letters as in "Position of turnover notches" table)</li>
    <li>l - number of reflectors</li>
    <li>definitions of reflectors R0,...,Rl-1 - permutation of the alphabet</li>
</ul>

A set of p tasks to perform: (each task consists of 2 parts: machine setup and a message to encrypt)
<ul>
  <li>p number of tasks</li>
  <li>k - number of rotors in the machine</li>
  <li>k pairs K0,...,Kk-1 - where Ki=(j, t), where j is an index of a copy of rotor Wj and t is its initial position (rotors are given in order from fastest to slowest; initial position of a rotor - it is set as if it was rotated (no actual rotations occur) prior to encoding, e.g. 1 - rotor is set as stated in permutation, 2 - it is shifted by one letter, etc.)</li>
  <li>r index of a reflector Rr</li>
  <li>a sequence of numbers separated by whitespaces to encrypt, ending with the 0 character</li>
</ul>

### Output
encrypted sequences of numbers (without the 0 character)
