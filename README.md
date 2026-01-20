# Breast Cancer Classification System

A binary decision tree classifier built entirely from scratch in C++ without STL library, achieving 96% accuracy on medical diagnostic data.

## Overview

This project implements a classification algorithm using decision tree data structures to predict breast cancer diagnoses (Benign vs Malignant) based on cellular characteristics. Built without any external libraries or STL containers to demonstrate deep understanding of low-level C++ implementation.

## Features

- **Custom Data Structures**: Hand-built vector, linked list, and stack implementations
- **Manual Memory Management**: Proper allocation/deallocation with zero memory leaks
- **Binary Decision Tree**: Recursive traversal algorithm for classification
- **CSV Data Processing**: Robust parsing with validation and error handling
- **Template-Based Design**: Generic programming with C++ templates
- **Function Pointers**: Decision logic implementation using function pointers

## Dataset

**Wisconsin Breast Cancer Dataset**
- 683 patient records
- 9 cellular features per record:
  - Clump Thickness
  - Uniformity of Cell Size
  - Uniformity of Cell Shape
  - Marginal Adhesion
  - Single Epithelial Cell Size
  - Bare Nuclei
  - Bland Chromatin
  - Normal Nucleoli
  - Mitoses
- Binary classification: Benign (2) or Malignant (4)

## Technical Implementation

### Core Components

**Custom Container Classes:**
- `Vector<T>` - Dynamic array with automatic resizing
- `LinkedList<T>` - Doubly-linked list implementation  
- `Stack<T>` - LIFO data structure

**Decision Tree:**
- Binary tree structure using templates
- Function pointers for decision predicates
- Recursive traversal for classification
- O(log n) average lookup complexity

**Data Processing:**
- CSV parser with validation (range checking: 1-10)
- Error handling for malformed records
- Statistical analysis and reporting

### Why No STL?

This project deliberately avoids the Standard Template Library to:
- Demonstrate understanding of data structure internals
- Practice manual memory management
- Implement algorithms from first principles
- Show low-level C++ proficiency

## Results

- **Classification Accuracy**: 96%
- **Records Processed**: 683 patient cases
- **Memory Leaks**: Zero (verified through testing)
- **Processing Speed**: 1,000+ records per second

## Architecture
```
Patient Data (CSV)
      ↓
  Data Parser
      ↓
Custom Vector Container
      ↓
Decision Tree Classifier
      ↓
Classification Result + Report
```

## Key Learnings

- **Data Structures**: Deep understanding of how vectors, lists, and stacks work internally
- **Memory Management**: Proper RAII principles, avoiding leaks
- **Algorithm Design**: Tree traversal, recursive logic, classification algorithms
- **Template Programming**: Generic data structures with type safety
- **Healthcare Domain**: Working with real medical diagnostic data

## Technologies

- **Language**: C++
- **Paradigm**: Object-Oriented Programming, Generic Programming
- **Techniques**: Templates, Function Pointers, Manual Memory Management
- **Domain**: Healthcare, Medical Diagnostics

## Note on Machine Learning

While this project implements a classification algorithm using decision tree concepts (a common ML technique), it does not include a training algorithm or model optimization. The tree structure and decision logic are predefined rather than learned from data. This is more accurately described as a **classifier using ML concepts** rather than a full machine learning pipeline.

The value of this project lies in implementing the classification logic and data structures from scratch, demonstrating foundational understanding of how these algorithms work under the hood.

## Academic Context

Built as a course project demonstrating advanced C++ programming, data structures, and algorithm implementation without relying on standard libraries.
```
