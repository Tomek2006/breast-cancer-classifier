/**	file main.cpp
	author : Tomek Marek
	date : 2025-12-12
	purpose: Main program for Breast Cancer Decision Tree classification
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "BinaryDecisionTree.h"
#include "PatientLogic.h"

using namespace std;
using Patient = PatientLogic::patient;

// Function to Validate the data
bool isValidPatient(const Patient& p) {
	
	return (p.ClumpThickness >= 1 && p.ClumpThickness <= 10 &&
		p.UniformityOfCellSize >= 1 && p.UniformityOfCellSize <= 10 &&
		p.UniformityOfCellShape >= 1 && p.UniformityOfCellShape <= 10 &&
		p.MarginalAdhesion >= 1 && p.MarginalAdhesion <= 10 &&
		p.SingleEpithelialCellSize >= 1 && p.SingleEpithelialCellSize <= 10 &&
		p.BareNuclei >= 1 && p.BareNuclei <= 10 &&
		p.BlandChromatin >= 1 && p.BlandChromatin <= 10 &&
		p.NormalNucleoli >= 1 && p.NormalNucleoli <= 10 &&
		p.Mitosis >= 1 && p.Mitosis <= 10);
}

// Function to read patients from CSV file
vector<Patient> readPatientsFromFile(const string& filename, int& invalidCount) {
	vector<Patient> patients;
	ifstream file(filename);
	string line;
	invalidCount = 0;

	if (!file.is_open()) {
		cerr << "Error: Could not open file " << filename << endl;
		return patients;
	}

	while (getline(file, line)) {
		if (line.empty()) continue;

		stringstream ss(line);
		string cell;
		Patient patient;
		vector<string> values;

		// add commas
		while (getline(ss, cell, ',')) {
			values.push_back(cell);
		}

		// Check if we have enough values (should be 11: sample code + 9 attributes + class)
		// + convert to ints
		if (values.size() >= 11) {
			try {
				patient.SampleCodeNumber = stoi(values[0]);
				patient.ClumpThickness = stoi(values[1]);
				patient.UniformityOfCellSize = stoi(values[2]);
				patient.UniformityOfCellShape = stoi(values[3]);
				patient.MarginalAdhesion = stoi(values[4]);
				patient.SingleEpithelialCellSize = stoi(values[5]);
				patient.BareNuclei = stoi(values[6]);
				patient.BlandChromatin = stoi(values[7]);
				patient.NormalNucleoli = stoi(values[8]);
				patient.Mitosis = stoi(values[9]);
				patient.Class = stoi(values[10]); 

				if (isValidPatient(patient)) {
					patients.push_back(patient);
				}
				else {
					invalidCount++;
					cout << "Invalid data for sample: " << patient.SampleCodeNumber << endl;
				}
			}
			catch (const exception& e) {
				invalidCount++;
				cout << "Error parsing patient data: " << e.what() << endl;
				//tell patient what error
			}
		}
		else {
			invalidCount++;
			cout << "Insufficient data in line: " << line << endl;
		}
	}

	file.close();
	return patients;
}

// Function to write patients to a CSV file
void writePatientsToFile(const vector<Patient>& patients, const string& filename) {
	ofstream file(filename);

	if (!file.is_open()) {
		cerr << "Error: Could not create file " << filename << endl;
		return;
	}

	for (const auto& patient : patients) {
		file << patient.SampleCodeNumber << ","
			<< patient.ClumpThickness << ","
			<< patient.UniformityOfCellSize << ","
			<< patient.UniformityOfCellShape << ","
			<< patient.MarginalAdhesion << ","
			<< patient.SingleEpithelialCellSize << ","
			<< patient.BareNuclei << ","
			<< patient.BlandChromatin << ","
			<< patient.NormalNucleoli << ","
			<< patient.Mitosis << ","
			<< patient.Class << endl;
	}

	file.close();
}


//Build tree
BinaryDecisionTree<PatientLogic::patient>* buildDecisionTree() {
	BinaryDecisionTree<PatientLogic::patient>* benign = new BinaryDecisionTree<PatientLogic::patient>(2);
	BinaryDecisionTree<PatientLogic::patient>* malignant = new BinaryDecisionTree<PatientLogic::patient>(4);

	auto* margAdhesion_le3_left = new BinaryDecisionTree<PatientLogic::patient>(
		PatientLogic::MarginalAdhesion_LessOREqual_3, malignant, benign);

	auto* margAdhesion_le3_right = new BinaryDecisionTree<PatientLogic::patient>(
		PatientLogic::MarginalAdhesion_LessOREqual_3, benign, malignant);

	auto* margAdhesion_le5 = new BinaryDecisionTree<PatientLogic::patient>(
		PatientLogic::MarginalAdhesion_LessOREqual_5, benign, malignant);

	auto* blandChromatin_le2 = new BinaryDecisionTree<PatientLogic::patient>(
		PatientLogic::BlandChromatin_LessOREqual_2, margAdhesion_le3_left, malignant);

	auto* clumpThickness_le3 = new BinaryDecisionTree<PatientLogic::patient>(
		PatientLogic::ClumpThickness_LessOREqual_3, benign, blandChromatin_le2);

	auto* clumpThickness_le5 = new BinaryDecisionTree<PatientLogic::patient>(
		PatientLogic::ClumpThickness_LessOREqual_5, benign, malignant);

	auto* uniformityCellSize_le3 = new BinaryDecisionTree<PatientLogic::patient>(
		PatientLogic::UniformityOfCellSize_LessOREqual_3, malignant, margAdhesion_le5);

	auto* clumpThickness_le6 = new BinaryDecisionTree<PatientLogic::patient>(
		PatientLogic::ClumpThickness_LessOREqual_6, uniformityCellSize_le3, malignant);

	auto* bareNuclei_le2 = new BinaryDecisionTree<PatientLogic::patient>(
		PatientLogic::BareNuclei_LessOREqual_2, margAdhesion_le3_right, clumpThickness_le6);

	auto* uniformityCellSize_le4 = new BinaryDecisionTree<PatientLogic::patient>(
		PatientLogic::UniformityOfCellSize_LessOREqual_4, bareNuclei_le2, malignant);

	auto* uniformityCellShape_le2 = new BinaryDecisionTree<PatientLogic::patient>(
		PatientLogic::UniformityOfCellShape_LessOREqual_2, clumpThickness_le5, uniformityCellSize_le4);

	auto* bareNuclei_le3 = new BinaryDecisionTree<PatientLogic::patient>(
		PatientLogic::BareNuclei_LessOREqual_3, benign, clumpThickness_le3);

	auto* root = new BinaryDecisionTree<PatientLogic::patient>(
		PatientLogic::Uniformity_OfCellSize_LessOREqual_2, bareNuclei_le3, uniformityCellShape_le2);

	return root;
}

int main()
{
	cout << "Breast Cancer Decision Tree Classifier" << endl;
	cout << "**************************************" << endl;
	cout << "**************************************" << endl;


	// Read  data
	int invalidCount = 0;
	vector<Patient> patients = readPatientsFromFile("unformatted_data_v1.0.0.csv", invalidCount);

	if (patients.empty()) {
		cerr << "No valid patient data found. Please check the input file." << endl;
		return 1;
	}

	// Build the decision tree
	BinaryDecisionTree<PatientLogic::patient>* decisionTree = buildDecisionTree();

	// Classify patient
	int benignCount = 0;
	int malignantCount = 0;

	for (auto& patient : patients) {
		int diagnosis = decisionTree->classify(patient);
		patient.Class = diagnosis;

		if (diagnosis == 2) {
			benignCount++;
		}
		else if (diagnosis == 4) {
			malignantCount++;
		}
	}

	// Write results to output file
	writePatientsToFile(patients, "results.csv");

	// summary
	cout << "\nEverything is Completed!" << endl;
	cout << "*******************" << endl;
	cout << "Total Patients Processed: " << patients.size() << endl;
	cout << "Total Benign: " << benignCount << endl;
	cout << "Total Malignant: " << malignantCount << endl;
	cout << "Total Invalid Patient: " << invalidCount << endl;
	cout << "\nResults saved to: results.csv" << endl;

	// clean
	delete decisionTree;

	return 0;
}