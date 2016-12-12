/**
 * @file preprocess_split_main.cpp
<<<<<<< HEAD
 * @author Keon Woo Kim
 *
 * split data CLI executable
=======
 * @author Keon Kim
 *
 * split data CLI executable
 *
 * mlpack is free software; you may redistribute it and/or modify it under the
 * terms of the 3-clause BSD license.  You should have received a copy of the
 * 3-clause BSD license along with mlpack.  If not, see
 * http://www.opensource.org/licenses/BSD-3-Clause for more information.
>>>>>>> mlpack/master
 */
#include <mlpack/core.hpp>
#include <mlpack/core/data/split_data.hpp>

PROGRAM_INFO("Split Data", "This utility takes a dataset and optionally labels "
    "and splits them into a training set and a test set. Before the split, the "
    "points in the dataset are randomly reordered. The percentage of the "
    "dataset to be used as the test set can be specified with the --test_ratio "
    "(-r) option; the default is 0.2 (20%)."
    "\n\n"
    "The program does not modify the original file, but instead makes separate "
<<<<<<< HEAD
    "files to save the training and test files; you can specify the file names "
    "with --training_file (-t) and --test_file (-T). If these options are not "
    "specified, the program automatically names the training and test file by "
    "prepending 'train_' and 'test_' to the dataset filename (which was "
    "specified by --input_file)."
=======
    "files to save the training and test files; The program requires you to "
    "specify the file names with --training_file (-t) and --test_file (-T)."
>>>>>>> mlpack/master
    "\n\n"
    "Optionally, labels can be also be split along with the data by specifying "
    "the --input_labels_file (-I) option. Splitting labels works the same way "
    "as splitting the data. The output training and test labels will be saved "
    "to the files specified by --training_labels_file (-l) and "
<<<<<<< HEAD
    "--test_labels_file (-L), respectively. If these options are not specified,"
    " then the program will automatically name the training labels and test "
    "labels file by prepending 'train_' and 'test_' to the labels filename "
    "(which was specified by --input_labels_file)."
    "\n\n"
    "So, a simple example where we want to split dataset.csv into "
    "train_dataset.csv and test_dataset.csv with 60% of the data in the "
    "training set and 40% of the dataset in the test set, we could run"
    "\n\n"
    "$ mlpack_preprocess_split -i dataset.csv -r 0.4"
=======
    "--test_labels_file (-L), respectively."
    "\n\n"
    "So, a simple example where we want to split dataset.csv into "
    "train.csv and test.csv with 60% of the data in the training set and 40% "
    "of the dataset in the test set, we could run"
    "\n\n"
    "$ mlpack_preprocess_split -i dataset.csv -t train.csv -T test.csv -r 0.4"
>>>>>>> mlpack/master
    "\n\n"
    "If we had a dataset in dataset.csv and associated labels in labels.csv, "
    "and we wanted to split these into training_set.csv, training_labels.csv, "
    "test_set.csv, and test_labels.csv, with 30% of the data in the test set, "
    "we could run"
    "\n\n"
    "$ mlpack_preprocess_split -i dataset.csv -I labels.csv -r 0.3\n"
    "> -t training_set.csv -l training_labels.csv -T test_set.csv\n"
    "> -L test_labels.csv");

// Define parameters for data.
<<<<<<< HEAD
PARAM_STRING_REQ("input_file", "File containing data,", "i");
// Define optional parameters.
PARAM_STRING("input_labels_file", "File containing labels", "I", "");
PARAM_STRING("training_file", "File name to save train data", "t", "");
PARAM_STRING("test_file", "File name to save test data", "T", "");
PARAM_STRING("training_labels_file", "File name to save train label", "l", "");
PARAM_STRING("test_labels_file", "File name to save test label", "L", "");

// Define optional test ratio, default is 0.2 (Test 20% Train 80%)
PARAM_DOUBLE("test_ratio", "Ratio of test set, if not set,"
=======
PARAM_MATRIX_IN_REQ("input", "Matrix containing data.", "i");
PARAM_MATRIX_OUT("training", "Matrix to save training data to.", "t");
PARAM_MATRIX_OUT("test", "Matrix to save test data to.", "T");

// Define optional parameters.
PARAM_UMATRIX_IN("input_labels", "Matrix containing labels.", "I");
PARAM_UMATRIX_OUT("training_labels", "Matrix to save train labels to.", "l");
PARAM_UMATRIX_OUT("test_labels", "Matrix to save test labels to.", "L");

// Define optional test ratio, default is 0.2 (Test 20% Train 80%).
PARAM_DOUBLE_IN("test_ratio", "Ratio of test set; if not set,"
>>>>>>> mlpack/master
    "the ratio defaults to 0.2", "r", 0.2);

using namespace mlpack;
using namespace arma;
using namespace std;

int main(int argc, char** argv)
{
  // Parse command line options.
  CLI::ParseCommandLine(argc, argv);
<<<<<<< HEAD
  const string inputFile = CLI::GetParam<string>("input_file");
  const string inputLabels = CLI::GetParam<string>("input_labels_file");
  string trainingFile = CLI::GetParam<string>("training_file");
  string testFile = CLI::GetParam<string>("test_file");
  string trainingLabelsFile = CLI::GetParam<string>("training_labels_file");
  string testLabelsFile = CLI::GetParam<string>("test_labels_file");
  const double testRatio = CLI::GetParam<double>("test_ratio");

  // Check on data parameters.
  if (trainingFile.empty())
  {
    trainingFile = "train_" + inputFile;
    Log::Warn << "You did not specify --training_file, so the training set file"
        << " name will be automatically set to '" << trainingFile << "'." 
        << endl;
  }
  if (testFile.empty())
  {
    testFile = "test_" + inputFile;
    Log::Warn << "You did not specify --test_file, so the test set file name "
        << "will be automatically set to '" << testFile << "'." << endl;
  }

  // Check on label parameters.
  if (!inputLabels.empty())
  {
    if (!CLI::HasParam("training_labels_file"))
    {
      trainingLabelsFile = "train_" + inputLabels;
      Log::Warn << "You did not specify --training_labels_file, so the training"
          << "set labels file name will be automatically set to '"
          << trainingLabelsFile << "'." << endl;
    }
    if (!CLI::HasParam("test_labels_file"))
    {
      testLabelsFile = "test_" + inputLabels;
      Log::Warn << "You did not specify --test_labels_file, so the test set "
        << "labels file name will be automatically set to '"
        << testLabelsFile << "'." << endl;
=======
  const double testRatio = CLI::GetParam<double>("test_ratio");

  // Make sure the user specified output filenames.
  if (!CLI::HasParam("training"))
    Log::Warn << "--training_file (-t) is not specified; no training set will "
        << "be saved!" << endl;
  if (!CLI::HasParam("test"))
    Log::Warn << "--test_file (-T) is not specified; no test set will be saved!"
        << endl;

  // Check on label parameters.
  if (CLI::HasParam("input_labels"))
  {
    if (!CLI::HasParam("training_labels"))
    {
      Log::Warn << "--training_labels_file (-l) is not specified; no training "
          << "set labels will be saved!" << endl;
    }
    if (!CLI::HasParam("test_labels"))
    {
      Log::Warn << "--test_labels_file (-L) is not specified; no test set "
          << "labels will be saved!" << endl;
>>>>>>> mlpack/master
    }
  }
  else
  {
<<<<<<< HEAD
    if (CLI::HasParam("training_labels_file")
        || CLI::HasParam("test_labels_file"))
    {
      Log::Fatal << "When specifying --training_labels_file or "
          << "--test_labels_file, you must also specify --input_labels. "
          << endl;
    }
=======
    if (CLI::HasParam("training_labels"))
      Log::Warn << "--training_labels_file ignored because --input_labels is "
          << "not specified." << endl;
    if (CLI::HasParam("test_labels"))
      Log::Warn << "--test_labels_file ignored because --input_labels is not "
          << "specified." << endl;
>>>>>>> mlpack/master
  }

  // Check test_ratio.
  if (CLI::HasParam("test_ratio"))
  {
    if ((testRatio < 0.0) || (testRatio > 1.0))
    {
      Log::Fatal << "Invalid parameter for test_ratio; "
          << "--test_ratio must be between 0.0 and 1.0." << endl;
    }
  }
  else // If test_ratio is not set, warn the user.
  {
    Log::Warn << "You did not specify --test_ratio, so it will be automatically"
        << " set to 0.2." << endl;
  }

  // Load the data.
<<<<<<< HEAD
  arma::mat data;
  data::Load(inputFile, data, true);

  // If parameters for labels exist, we must split the labels too.
  if (CLI::HasParam("input_labels_file"))
  {
    arma::mat labels;
    data::Load(inputLabels, labels, true);
    arma::rowvec labelsRow = labels.row(0);
=======
  arma::mat& data = CLI::GetParam<arma::mat>("input");

  // If parameters for labels exist, we must split the labels too.
  if (CLI::HasParam("input_labels"))
  {
    arma::Mat<size_t>& labels =
        CLI::GetParam<arma::Mat<size_t>>("input_labels");
    arma::Row<size_t> labelsRow = labels.row(0);
>>>>>>> mlpack/master

    const auto value = data::Split(data, labelsRow, testRatio);
    Log::Info << "Training data contains " << get<0>(value).n_cols << " points."
        << endl;
    Log::Info << "Test data contains " << get<1>(value).n_cols << " points."
        << endl;

<<<<<<< HEAD
    data::Save(trainingFile, get<0>(value), false);
    data::Save(testFile, get<1>(value), false);
    data::Save(trainingLabelsFile, get<2>(value), false);
    data::Save(testLabelsFile, get<3>(value), false);
=======
    if (CLI::HasParam("training"))
      CLI::GetParam<arma::mat>("training") = std::move(get<0>(value));
    if (CLI::HasParam("test"))
      CLI::GetParam<arma::mat>("test") = std::move(get<1>(value));
    if (CLI::HasParam("training_labels"))
      CLI::GetParam<arma::Mat<size_t>>("training_labels") =
          std::move(get<2>(value));
    if (CLI::HasParam("test_labels"))
      CLI::GetParam<arma::Mat<size_t>>("test_labels") =
          std::move(get<3>(value));
>>>>>>> mlpack/master
  }
  else // We have no labels, so just split the dataset.
  {
    const auto value = data::Split(data, testRatio);
    Log::Info << "Training data contains " << get<0>(value).n_cols << " points."
        << endl;
    Log::Info << "Test data contains " << get<1>(value).n_cols << " points."
        << endl;

<<<<<<< HEAD
    data::Save(trainingFile, get<0>(value), false);
    data::Save(testFile, get<1>(value), false);
=======
    if (CLI::HasParam("training"))
      CLI::GetParam<arma::mat>("training") = std::move(get<0>(value));
    if (CLI::HasParam("test"))
      CLI::GetParam<arma::mat>("test") = std::move(get<1>(value));
>>>>>>> mlpack/master
  }
}
