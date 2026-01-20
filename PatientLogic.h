/**	file PatientLogic.h
	author : Tomek Marek
	date : 2025-12-12
	purpose: Defines the Patient struct and specifies the logic that the tree will use
*/
#pragma once
#include <iostream>
#include <string>
class PatientLogic {
public:
	//patient class to create an object to examine
	struct patient
	{
		int SampleCodeNumber;
		int ClumpThickness;
		int UniformityOfCellSize;
		int UniformityOfCellShape;
		int MarginalAdhesion;
		int SingleEpithelialCellSize;
		int BareNuclei;
		int BlandChromatin;
		int NormalNucleoli;
		int Mitosis;
		int Class;

	};

	//Setting up the logic function for each node

	 static bool Uniformity_OfCellSize_LessOREqual_2(const patient& p) {
		return p.UniformityOfCellSize <= 2;
	}

	 static bool BareNuclei_LessOREqual_3(const patient& p) {
		 return p.BareNuclei <= 3;
	 }

	 static bool ClumpThickness_LessOREqual_3(const patient& p) {
		 return p.ClumpThickness <= 3;
	 }

	 static bool BlandChromatin_LessOREqual_2(const patient& p) {
		 return p.BlandChromatin <= 2;
	 }

	 static bool MarginalAdhesion_LessOREqual_3(const patient& p) {
		 return p.MarginalAdhesion <= 3;
	 }

	 static bool UniformityOfCellShape_LessOREqual_2(const patient& p) {
		 return p.UniformityOfCellShape <= 2;
	 }
	 static bool ClumpThickness_LessOREqual_5(const patient& p) {
		 return p.ClumpThickness <= 5;
	 }

	 static bool UniformityOfCellSize_LessOREqual_4(const patient& p) {
		 return p.UniformityOfCellSize <= 4;
	 }

	 static bool BareNuclei_LessOREqual_2(const patient& p) {
		 return p.BareNuclei <= 2;
	 }
	 static bool ClumpThickness_LessOREqual_6(const patient& p) {
		 return p.ClumpThickness <= 6;
	 }
	 static bool UniformityOfCellSize_LessOREqual_3(const patient& p) {
		 return p.UniformityOfCellSize <= 3;
	 }
	 static bool MarginalAdhesion_LessOREqual_5(const patient& p) {
		 return p.MarginalAdhesion <= 5;
	 }

	

};