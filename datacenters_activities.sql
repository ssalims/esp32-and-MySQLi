-- phpMyAdmin SQL Dump
-- version 4.8.4
-- https://www.phpmyadmin.net/
--
-- Host: localhost
-- Generation Time: Feb 09, 2021 at 05:46 AM
-- Server version: 10.1.37-MariaDB
-- PHP Version: 7.3.0

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `datacenters_activities`
--

-- --------------------------------------------------------

--
-- Table structure for table `room_dc230`
--

CREATE TABLE `room_dc230` (
  `id` int(11) NOT NULL,
  `logDateTime` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `rackID` varchar(255) NOT NULL,
  `tempValue` varchar(255) NOT NULL,
  `humidValue` varchar(255) NOT NULL,
  `rackStatus` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `room_dc230`
--

INSERT INTO `room_dc230` (`id`, `logDateTime`, `rackID`, `tempValue`, `humidValue`, `rackStatus`) VALUES
(1, '2021-02-09 01:59:08', '', '', '', ''),
(2, '2021-02-09 02:04:38', 'r1', '24', '70', 'Normal');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `room_dc230`
--
ALTER TABLE `room_dc230`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `room_dc230`
--
ALTER TABLE `room_dc230`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
