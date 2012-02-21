#include <exception>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include "LogisticRegressionClassifier.h"
#include "stringHelp.h"

const unsigned int gradientAscentIterationsLimit = 1;
const float w_0 = 1.0f;
const float eta = -0.1f;
const float lambda = 0.5f;

void LogisticRegressionClassifier::train( const DataSet& data ) {
  // Add new vocab for all classes of documents in data.
  m_vocab.clear();
  for ( unsigned int i = 0; i < data.m_docs.size(); i++ ) {
    addVocab( data.m_docs[i], m_vocab );
  }

  // Create 0 weight vector. 
  m_weights.clear();
  map<string, unsigned int>::iterator vocabIt;
  for ( vocabIt = m_vocab.begin(); vocabIt != m_vocab.end(); vocabIt++ ) {
    m_weights[vocabIt->first] = 0.0f;
  }

  // Copy class labels from data.
  m_classes.clear();
  for ( unsigned int i = 0; i < data.m_classes.size(); i++ ) {
    m_classes.push_back( data.m_classes[i].first );
  }

  gradientAscent( data );

  cout << "THE WEIGHTS VECTOR" << endl;
  for ( map<string,float>::iterator weightIt = m_weights.begin(); weightIt != m_weights.end(); weightIt++ ) {

  }
}

void LogisticRegressionClassifier::gradientAscent( const DataSet& data ) {
  map<string, float>::iterator weightIt;
  // Don't run until convergence. Run specified number of times.
  for ( unsigned int i = 0; i < gradientAscentIterationsLimit; i++ ) {
    cout << "Running gradient descent iteration " << i << endl;
    for ( weightIt = m_weights.begin(); weightIt != m_weights.end(); weightIt++ ) {
      cout << "Updating weight for (" << weightIt->first << "," << weightIt->second << ")" << endl;
      weightIt->second += (eta * conditionalAPosteriori(weightIt->first, data));
      cout << "       Updated weight = " << weightIt->second << endl;
    }
  }
}

float LogisticRegressionClassifier::conditionalAPosteriori( string token, const DataSet& data ) {
  float sum = 0.0f;
  for ( unsigned int i = 0; i < data.m_docs.size(); i++ ) {
    for ( unsigned int j = 0; j < data.m_docs[i].size(); j++ ) {
      // Create document vocabulary map.
      map<string, unsigned int> docVocab;
      addVocab( data.m_docs[i][j], docVocab );

      map<string, unsigned int>::iterator docVocabIt;
      docVocabIt = docVocab.find( token );
      if ( docVocabIt != docVocab.end() ) {
        sum += ( (float)(docVocabIt->second) * ((float)i - pHat(docVocab)) );
      }
    }
  }

  return (-lambda * m_weights[token]) + sum;
}

float LogisticRegressionClassifier::pHat( map<string, unsigned int>& docVocab ) {
  //cout << "pHatting it up" << endl;
  map<string, float>::iterator weightIt;
  map<string, unsigned int>::iterator docVocabIt;
  float sum = 0.0f;

  for ( docVocabIt = docVocab.begin(); docVocabIt != docVocab.end(); docVocabIt++ ) {
    weightIt = m_weights.find( docVocabIt->first );

    // If the specified token isn't in the weights, we don't know what its 
    // weight is. Give it 0 to discard it.
    sum += ( weightIt == m_weights.end() ? 0.0f : ((float)docVocabIt->second * weightIt->second) );
  }

  float temp = (float)exp(w_0 + sum);
  return (temp / (1.0f + temp)); 
}

float LogisticRegressionClassifier::test( const DataSet &data ) {
  unsigned int correctClassifications = 0;
  unsigned int classification = 0;

  // Count number of documents total.
  unsigned int numDocs = 0;
  for ( unsigned int i = 0; i < data.m_docs.size(); i++ ) {
    numDocs += data.m_docs[i].size();
  }

  // Classify each document, track the number of correct classifications.
  for ( unsigned int i = 0; i < data.m_docs.size(); i++ ) {
    for ( unsigned int j = 0; j < data.m_docs[i].size(); j++ ) {
      classification = classify( data.m_docs[i][j] );
      if ( classification == i ) {
        correctClassifications++;
      }
    }
  }

  return (float)correctClassifications / (float)numDocs;
}

unsigned int LogisticRegressionClassifier::classify( const Document& doc ) {
  // Create document vocabulary map.
  map<string, unsigned int> docVocab;
  addVocab( doc, docVocab );

  map<string, float>::iterator weightIt;
  map<string, unsigned int>::iterator docVocabIt;
  float sum = w_0;

  for ( docVocabIt = docVocab.begin(); docVocabIt != docVocab.end(); docVocabIt++ ) {
    string token = docVocabIt->first;
    weightIt = m_weights.find( token );

    // If the specified token isn't in the weights, we don't know what its 
    // weight is. Give it 0 to discard it.
    sum += ( weightIt == m_weights.end() ? 0.0f : ((float)docVocabIt->second * weightIt->second) );
  }

  return (sum > 0.0f ? 0 : 1);
}
