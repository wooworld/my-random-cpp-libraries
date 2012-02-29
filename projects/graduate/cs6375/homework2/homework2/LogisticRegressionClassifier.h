#ifndef LOGISTIC_REGRESSION_CLASSIFIER_H
#define LOGISTIC_REGRESSION_CLASSIFIER_H

#include <map>
#include <vector>
#include <string>
#include "DataSet.h"
#include "Document.h"
#include "Classifier.h"

using namespace std;

class LogisticRegressionClassifier : public Classifier {
public:
  void train( const DataSet& data );
  float test( const DataSet& data );
  unsigned int classify( const Document& doc );  

protected:  
  void createVocabToVectorMap();
  void gradientAscent();
  double pHat( unsigned int idx );

  unsigned int m_numDocs;
  unsigned int m_numAttrs;

  Dictionary m_vocabToVector;

  vector<vector<unsigned int> > m_data;
  vector<double> m_w;
  vector<double> m_dw;
  vector<double> m_pr; 
};

#endif

/*
Professor's pseudo code:

Data = m x (n+2) matrix; each row is training example
Data[i][n+1] = class attr
Data[i][0] = w_0 = 1.0

for each example i
  compute pr[i] = probability(class=1 | data[i], w)

array dw[0..n] = 0
for i=0..n
  for j=0..m-1
    dw[i] = dw[i] + Data[j][i]*(Data[i][j] - pr[j]);
for i=0..n
  w[i] = w[i] - eta*(dw[i] - lambda*w[i]);
*/